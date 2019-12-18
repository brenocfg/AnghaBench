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
struct TYPE_4__ {int v_flag; } ;

/* Variables and functions */
 int VLOCKLOCAL ; 
 int /*<<< orphan*/  lf_abort_advlocks (TYPE_1__*) ; 

__attribute__((used)) static void
vnode_abort_advlocks(vnode_t vp)
{
	if (vp->v_flag & VLOCKLOCAL)
		lf_abort_advlocks(vp);
}