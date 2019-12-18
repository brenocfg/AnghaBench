#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* libzfs_fru_hash; int /*<<< orphan*/ * libzfs_topo_hdl; TYPE_2__* libzfs_fru_list; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_7__ {struct TYPE_7__* zf_fru; struct TYPE_7__* zf_device; struct TYPE_7__* zf_next; } ;
typedef  TYPE_2__ libzfs_fru_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ZFS_FRU_HASH_SIZE ; 
 int /*<<< orphan*/  _topo_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _topo_snap_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
libzfs_fru_clear(libzfs_handle_t *hdl, boolean_t final)
{
	libzfs_fru_t *frup;

	while ((frup = hdl->libzfs_fru_list) != NULL) {
		hdl->libzfs_fru_list = frup->zf_next;
		free(frup->zf_device);
		free(frup->zf_fru);
		free(frup);
	}

	hdl->libzfs_fru_list = NULL;

	if (hdl->libzfs_topo_hdl != NULL) {
		_topo_snap_release(hdl->libzfs_topo_hdl);
		_topo_close(hdl->libzfs_topo_hdl);
		hdl->libzfs_topo_hdl = NULL;
	}

	if (final) {
		free(hdl->libzfs_fru_hash);
	} else if (hdl->libzfs_fru_hash != NULL) {
		bzero(hdl->libzfs_fru_hash,
		    ZFS_FRU_HASH_SIZE * sizeof (void *));
	}
}