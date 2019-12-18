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
struct vfsmount {int /*<<< orphan*/  mnt_writers; int /*<<< orphan*/  mnt_devname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vfsmount*) ; 
 int /*<<< orphan*/  mnt_cache ; 
 int /*<<< orphan*/  mnt_free_id (struct vfsmount*) ; 

void free_vfsmnt(struct vfsmount *mnt)
{
	kfree(mnt->mnt_devname);
	mnt_free_id(mnt);
#ifdef CONFIG_SMP
	free_percpu(mnt->mnt_writers);
#endif
	kmem_cache_free(mnt_cache, mnt);
}