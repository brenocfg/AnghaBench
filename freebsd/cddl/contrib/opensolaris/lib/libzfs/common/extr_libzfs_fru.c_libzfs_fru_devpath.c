#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  libzfs_topo_hdl; TYPE_2__** libzfs_fru_hash; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_6__ {char const* zf_device; int /*<<< orphan*/  zf_fru; struct TYPE_6__* zf_next; } ;
typedef  TYPE_2__ libzfs_fru_t ;

/* Variables and functions */
 size_t ZFS_FRU_HASH_SIZE ; 
 scalar_t__ _topo_fmri_strcmp_noauth (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libzfs_fru_refresh (TYPE_1__*) ; 

const char *
libzfs_fru_devpath(libzfs_handle_t *hdl, const char *fru)
{
	libzfs_fru_t *frup;
	size_t idx;

	if (hdl->libzfs_fru_hash == NULL)
		libzfs_fru_refresh(hdl);

	if (hdl->libzfs_fru_hash == NULL)
		return (NULL);

	for (idx = 0; idx < ZFS_FRU_HASH_SIZE; idx++) {
		for (frup = hdl->libzfs_fru_hash[idx]; frup != NULL;
		    frup = frup->zf_next) {
			if (_topo_fmri_strcmp_noauth(hdl->libzfs_topo_hdl,
			    fru, frup->zf_fru))
				return (frup->zf_device);
		}
	}

	return (NULL);
}