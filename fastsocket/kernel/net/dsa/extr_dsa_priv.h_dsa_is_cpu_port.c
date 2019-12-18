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
struct dsa_switch {scalar_t__ index; TYPE_1__* dst; } ;
struct TYPE_2__ {scalar_t__ cpu_switch; int cpu_port; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dsa_is_cpu_port(struct dsa_switch *ds, int p)
{
	return !!(ds->index == ds->dst->cpu_switch && p == ds->dst->cpu_port);
}