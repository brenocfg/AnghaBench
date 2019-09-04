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
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  VCREATESIZE ; 
 int /*<<< orphan*/  VNCREATE_FLAVOR ; 
 int vnode_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
vnode_create_empty(vnode_t *vpp)
{
	*vpp = NULLVP;
	return (vnode_create_internal(VNCREATE_FLAVOR, VCREATESIZE, NULL,
	    vpp, 0));
}