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
typedef  scalar_t__ u32 ;
struct clocksource {int dummy; } ;
typedef  scalar_t__ cycle_t ;

/* Variables and functions */
 scalar_t__ TCN ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ m68328_tick_cnt ; 

__attribute__((used)) static cycle_t m68328_read_clk(struct clocksource *cs)
{
	unsigned long flags;
	u32 cycles;

	local_irq_save(flags);
	cycles = m68328_tick_cnt + TCN;
	local_irq_restore(flags);

	return cycles;
}