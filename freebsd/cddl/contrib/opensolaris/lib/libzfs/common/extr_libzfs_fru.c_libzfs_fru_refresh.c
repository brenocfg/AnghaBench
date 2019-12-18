#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  topo_walk_t ;
typedef  int /*<<< orphan*/  topo_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/ * libzfs_fru_hash; int /*<<< orphan*/ * libzfs_topo_hdl; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME_HC ; 
 int /*<<< orphan*/  TOPO_VERSION ; 
 int /*<<< orphan*/  TOPO_WALK_CHILD ; 
 int /*<<< orphan*/  ZFS_FRU_HASH_SIZE ; 
 int /*<<< orphan*/ * _topo_dlhandle ; 
 int /*<<< orphan*/  _topo_hdl_strfree (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * _topo_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 char* _topo_snap_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _topo_walk_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _topo_walk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  _topo_walk_step (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libzfs_fru_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libzfs_fru_gather ; 

void
libzfs_fru_refresh(libzfs_handle_t *hdl)
{
	int err;
	char *uuid;
	topo_hdl_t *thp;
	topo_walk_t *twp;

	if (_topo_dlhandle == NULL)
		return;

	/*
	 * Clear the FRU hash and initialize our basic structures.
	 */
	libzfs_fru_clear(hdl, B_FALSE);

	if ((hdl->libzfs_topo_hdl = _topo_open(TOPO_VERSION,
	    NULL, &err)) == NULL)
		return;

	thp = hdl->libzfs_topo_hdl;

	if ((uuid = _topo_snap_hold(thp, NULL, &err)) == NULL)
		return;

	_topo_hdl_strfree(thp, uuid);

	if (hdl->libzfs_fru_hash == NULL &&
	    (hdl->libzfs_fru_hash =
	    calloc(ZFS_FRU_HASH_SIZE, sizeof (void *))) == NULL)
		return;

	/*
	 * We now have a topo snapshot, so iterate over the hc topology looking
	 * for disks to add to the hash.
	 */
	twp = _topo_walk_init(thp, FM_FMRI_SCHEME_HC,
	    libzfs_fru_gather, hdl, &err);
	if (twp != NULL) {
		(void) _topo_walk_step(twp, TOPO_WALK_CHILD);
		_topo_walk_fini(twp);
	}
}