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
typedef  int /*<<< orphan*/  sched_group_t ;
typedef  TYPE_1__* sched_entry_t ;
struct TYPE_3__ {int sched_pri; } ;

/* Variables and functions */

__attribute__((used)) __attribute__((always_inline))
static inline sched_group_t
group_for_entry(sched_entry_t entry)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-align"
	sched_group_t group = (sched_group_t)(entry - entry->sched_pri);
#pragma clang diagnostic pop
	return group;
}