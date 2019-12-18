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
union corpse_creation_gate {unsigned long corpses; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflight_corpses ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

unsigned long
total_corpses_count(void)
{
	union corpse_creation_gate gate;

	gate.value = atomic_load_explicit(&inflight_corpses, memory_order_relaxed);
	return gate.corpses;
}