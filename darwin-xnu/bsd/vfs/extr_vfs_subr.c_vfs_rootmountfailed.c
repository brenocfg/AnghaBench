#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mount {int dummy; } ;
typedef  TYPE_2__* mount_t ;
struct TYPE_9__ {TYPE_1__* mnt_vtable; } ;
struct TYPE_8__ {int /*<<< orphan*/  vfc_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  mac_mount_label_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int /*<<< orphan*/  mount_lock_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  vfs_unbusy (TYPE_2__*) ; 

__attribute__((used)) static void
vfs_rootmountfailed(mount_t mp) {

	mount_list_lock();
	mp->mnt_vtable->vfc_refcount--;
	mount_list_unlock();

	vfs_unbusy(mp);

	mount_lock_destroy(mp);

#if CONFIG_MACF
	mac_mount_label_destroy(mp);
#endif

	FREE_ZONE(mp, sizeof(struct mount), M_MOUNT);
}