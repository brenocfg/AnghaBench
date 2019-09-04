#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_3__ {scalar_t__ v_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_CACHE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 char* vfs_addname (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
vnode_getname(vnode_t vp)
{
        const char *name = NULL;
	
	NAME_CACHE_LOCK_SHARED();
	
	if (vp->v_name)
	        name = vfs_addname(vp->v_name, strlen(vp->v_name), 0, 0);
	NAME_CACHE_UNLOCK();

	return (name);
}