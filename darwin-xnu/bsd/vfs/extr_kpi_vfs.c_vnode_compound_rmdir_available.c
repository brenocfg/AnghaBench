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
 int /*<<< orphan*/  COMPOUND_VNOP_RMDIR ; 
 int vnode_compound_op_available (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vnode_compound_rmdir_available(vnode_t vp) 
{
	return vnode_compound_op_available(vp, COMPOUND_VNOP_RMDIR);
}