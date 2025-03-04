/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <stratosphere.hpp>
#include "lr_location_redirector.hpp"
#include "lr_registered_data.hpp"

namespace ams::lr {

    class AddOnContentLocationResolverImpl {
        private:
            /* Storage for RegisteredData entries by data id. */
            RegisteredStorages<ncm::DataId, 0x800> m_registered_storages;
        private:
            static ALWAYS_INLINE size_t GetStorageCapacity() {
                const auto version = hos::GetVersion();
                if (version >= hos::Version_12_0_0) {
                    return 0x8;
                } else if (version >= hos::Version_9_0_0) {
                    return 0x2;
                } else {
                    return 0x800;
                }
            }
        public:
            AddOnContentLocationResolverImpl() : m_registered_storages(GetStorageCapacity()) { /* ... */ }

            /* Actual commands. */
            Result ResolveAddOnContentPath(sf::Out<Path> out, ncm::DataId id);
            Result RegisterAddOnContentStorageDeprecated(ncm::DataId id, ncm::StorageId storage_id);
            Result RegisterAddOnContentStorage(ncm::DataId id, ncm::ApplicationId application_id, ncm::StorageId storage_id);
            Result UnregisterAllAddOnContentPath();
            Result RefreshApplicationAddOnContent(const sf::InArray<ncm::ApplicationId> &ids);
            Result UnregisterApplicationAddOnContent(ncm::ApplicationId id);
    };
    static_assert(lr::IsIAddOnContentLocationResolver<AddOnContentLocationResolverImpl>);

}
