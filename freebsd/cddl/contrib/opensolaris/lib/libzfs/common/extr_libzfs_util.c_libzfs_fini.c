#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ libzfs_sharetab; scalar_t__ libzfs_mnttab; int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libzfs_core_fini () ; 
 int /*<<< orphan*/  libzfs_fru_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libzfs_mnttab_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  namespace_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_uninit_libshare (TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_free_handles (TYPE_1__*) ; 

void
libzfs_fini(libzfs_handle_t *hdl)
{
	(void) close(hdl->libzfs_fd);
	if (hdl->libzfs_mnttab)
		(void) fclose(hdl->libzfs_mnttab);
	if (hdl->libzfs_sharetab)
		(void) fclose(hdl->libzfs_sharetab);
	zfs_uninit_libshare(hdl);
	zpool_free_handles(hdl);
#ifdef illumos
	libzfs_fru_clear(hdl, B_TRUE);
#endif
	namespace_clear(hdl);
	libzfs_mnttab_fini(hdl);
	libzfs_core_fini();
	free(hdl);
}