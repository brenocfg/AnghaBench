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

/* Variables and functions */
 int /*<<< orphan*/  rootvnode ; 
 int vnode_get (int /*<<< orphan*/ ) ; 

vnode_t  
vfs_rootvnode(void)
{
	int error;

	error = vnode_get(rootvnode);
	if (error)
		return ((vnode_t)0);
	else
		return rootvnode;
}