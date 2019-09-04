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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;

/* Variables and functions */
 int vnode_authattr_new_internal (int /*<<< orphan*/ ,struct vnode_attr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int 
vnode_authattr_new(vnode_t dvp, struct vnode_attr *vap, int noauth, vfs_context_t ctx)
{
	return vnode_authattr_new_internal(dvp, vap, noauth, NULL, ctx);
}