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
struct TYPE_3__ {int /*<<< orphan*/ * v_label; } ;

/* Variables and functions */
 scalar_t__ mac_label_vnodes ; 

int
mac_vnode_label_init_needed(vnode_t vp)
{
	return (mac_label_vnodes != 0 && vp->v_label == NULL);
}