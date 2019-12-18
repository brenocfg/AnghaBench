#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  libzfs_prop_debug; int /*<<< orphan*/ * libzfs_sharetab; int /*<<< orphan*/ * libzfs_mnttab; int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  MNTTAB ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_EXPORTS_PATH ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ libzfs_core_init () ; 
 scalar_t__ libzfs_load () ; 
 int /*<<< orphan*/  libzfs_mnttab_init (TYPE_1__*) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_init () ; 
 int /*<<< orphan*/  zpool_feature_init () ; 
 int /*<<< orphan*/  zpool_prop_init () ; 

libzfs_handle_t *
libzfs_init(void)
{
	libzfs_handle_t *hdl;

	if ((hdl = calloc(1, sizeof (libzfs_handle_t))) == NULL) {
		return (NULL);
	}

	if (libzfs_load() < 0) {
		free(hdl);
		return (NULL);
	}

	if ((hdl->libzfs_fd = open(ZFS_DEV, O_RDWR)) < 0) {
		free(hdl);
		return (NULL);
	}

	if ((hdl->libzfs_mnttab = fopen(MNTTAB, "r")) == NULL) {
		(void) close(hdl->libzfs_fd);
		free(hdl);
		return (NULL);
	}

	hdl->libzfs_sharetab = fopen(ZFS_EXPORTS_PATH, "r");

	if (libzfs_core_init() != 0) {
		(void) close(hdl->libzfs_fd);
		(void) fclose(hdl->libzfs_mnttab);
		(void) fclose(hdl->libzfs_sharetab);
		free(hdl);
		return (NULL);
	}

	zfs_prop_init();
	zpool_prop_init();
	zpool_feature_init();
	libzfs_mnttab_init(hdl);

	if (getenv("ZFS_PROP_DEBUG") != NULL) {
		hdl->libzfs_prop_debug = B_TRUE;
	}

	return (hdl);
}