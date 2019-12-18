#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct devfsmount {int /*<<< orphan*/ * plane_root; } ;
typedef  int /*<<< orphan*/  devdirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_free_hier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_free_name (int /*<<< orphan*/ *) ; 
 scalar_t__ devfs_nmountplanes ; 
 int /*<<< orphan*/  panic (char*) ; 

void
devfs_free_plane(struct devfsmount *devfs_mp_p)
{
	devdirent_t * dirent_p;

	dirent_p = devfs_mp_p->plane_root;
	if (dirent_p) {
		dev_free_hier(dirent_p);
		dev_free_name(dirent_p);
	}
	devfs_mp_p->plane_root = NULL;
	devfs_nmountplanes--;

	if (devfs_nmountplanes > (devfs_nmountplanes+1)) {
		panic("plane count wrapped around.\n");
	}
}