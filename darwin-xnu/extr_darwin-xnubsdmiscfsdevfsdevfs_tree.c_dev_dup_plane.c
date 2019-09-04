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
 int dev_dup_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,struct devfsmount*) ; 
 int /*<<< orphan*/  dev_root ; 
 int /*<<< orphan*/  devfs_nmountplanes ; 

int
dev_dup_plane(struct devfsmount *devfs_mp_p)
{
	devdirent_t *	new;
	int		error = 0;

	if ((error = dev_dup_entry(NULL, dev_root, &new, devfs_mp_p)))
	        return error;
	devfs_mp_p->plane_root = new;
	devfs_nmountplanes++;
	return error;
}