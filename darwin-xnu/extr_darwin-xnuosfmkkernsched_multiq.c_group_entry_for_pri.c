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
typedef  TYPE_1__* sched_group_t ;
typedef  int /*<<< orphan*/ * sched_entry_t ;
typedef  size_t integer_t ;
struct TYPE_3__ {int /*<<< orphan*/ * entries; } ;

/* Variables and functions */

__attribute__((used)) __attribute__((always_inline))
static inline sched_entry_t
group_entry_for_pri(sched_group_t group, integer_t pri)
{
	return &group->entries[pri];
}