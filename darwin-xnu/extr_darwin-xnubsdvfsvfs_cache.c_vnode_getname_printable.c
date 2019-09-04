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
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  dev_name ;
struct TYPE_4__ {int v_type; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_CACHE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
#define  VBLK 129 
#define  VCHR 128 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char,int,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char const* unknown_vnodename ; 
 char* vfs_addname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* vnode_getname (TYPE_1__*) ; 

const char *
vnode_getname_printable(vnode_t vp)
{
	const char *name = vnode_getname(vp);
	if (name != NULL)
		return name;
	
	switch (vp->v_type) {
		case VCHR:
		case VBLK:
			{
			/*
			 * Create an artificial dev name from
			 * major and minor device number
			 */
			char dev_name[64];
			(void) snprintf(dev_name, sizeof(dev_name),
					"%c(%u, %u)", VCHR == vp->v_type ? 'c':'b',
					major(vp->v_rdev), minor(vp->v_rdev));
			/*
			 * Add the newly created dev name to the name
			 * cache to allow easier cleanup. Also,
			 * vfs_addname allocates memory for the new name
			 * and returns it.
			 */
			NAME_CACHE_LOCK_SHARED();
			name = vfs_addname(dev_name, strlen(dev_name), 0, 0);
			NAME_CACHE_UNLOCK();
			return name;
			}
		default:
			return unknown_vnodename;
	}
}