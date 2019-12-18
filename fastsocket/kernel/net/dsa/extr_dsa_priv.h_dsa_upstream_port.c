#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dsa_switch_tree {size_t cpu_switch; int /*<<< orphan*/  cpu_port; } ;
struct dsa_switch {size_t index; TYPE_1__* pd; struct dsa_switch_tree* dst; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rtable; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 dsa_upstream_port(struct dsa_switch *ds)
{
	struct dsa_switch_tree *dst = ds->dst;

	/*
	 * If this is the root switch (i.e. the switch that connects
	 * to the CPU), return the cpu port number on this switch.
	 * Else return the (DSA) port number that connects to the
	 * switch that is one hop closer to the cpu.
	 */
	if (dst->cpu_switch == ds->index)
		return dst->cpu_port;
	else
		return ds->pd->rtable[dst->cpu_switch];
}