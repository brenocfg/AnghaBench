#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  nomount; } ;
typedef  TYPE_1__ recvflags_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_GATHER_MOUNT_ALWAYS ; 
 int ENOENT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int changelist_postfix (int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int zfs_receive_impl (int /*<<< orphan*/ *,char const*,char*,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfs_receive(libzfs_handle_t *hdl, const char *tosnap, nvlist_t *props,
    recvflags_t *flags, int infd, avl_tree_t *stream_avl)
{
	char *top_zfs = NULL;
	int err;
	int cleanup_fd;
	uint64_t action_handle = 0;
	char *originsnap = NULL;
	if (props) {
		err = nvlist_lookup_string(props, "origin", &originsnap);
		if (err && err != ENOENT)
			return (err);
	}

	cleanup_fd = open(ZFS_DEV, O_RDWR|O_EXCL);
	VERIFY(cleanup_fd >= 0);

	err = zfs_receive_impl(hdl, tosnap, originsnap, flags, infd, NULL, NULL,
	    stream_avl, &top_zfs, cleanup_fd, &action_handle, NULL);

	VERIFY(0 == close(cleanup_fd));

	if (err == 0 && !flags->nomount && top_zfs) {
		zfs_handle_t *zhp;
		prop_changelist_t *clp;

		zhp = zfs_open(hdl, top_zfs, ZFS_TYPE_FILESYSTEM);
		if (zhp != NULL) {
			clp = changelist_gather(zhp, ZFS_PROP_MOUNTPOINT,
			    CL_GATHER_MOUNT_ALWAYS, 0);
			zfs_close(zhp);
			if (clp != NULL) {
				/* mount and share received datasets */
				err = changelist_postfix(clp);
				changelist_free(clp);
			}
		}
		if (zhp == NULL || clp == NULL || err)
			err = -1;
	}
	if (top_zfs)
		free(top_zfs);

	return (err);
}