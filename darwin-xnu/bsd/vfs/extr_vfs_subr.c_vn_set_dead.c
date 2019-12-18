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
struct TYPE_3__ {int /*<<< orphan*/  v_lflag; int /*<<< orphan*/  v_type; int /*<<< orphan*/ * v_data; int /*<<< orphan*/  v_tag; int /*<<< orphan*/  v_op; int /*<<< orphan*/ * v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBAD ; 
 int /*<<< orphan*/  VL_DEAD ; 
 int /*<<< orphan*/  VT_NON ; 
 int /*<<< orphan*/  dead_vnodeop_p ; 

__attribute__((used)) static inline void
vn_set_dead(vnode_t vp)
{
	vp->v_mount = NULL;
	vp->v_op = dead_vnodeop_p;
	vp->v_tag = VT_NON;
	vp->v_data = NULL;
	vp->v_type = VBAD;
	vp->v_lflag |= VL_DEAD;
}