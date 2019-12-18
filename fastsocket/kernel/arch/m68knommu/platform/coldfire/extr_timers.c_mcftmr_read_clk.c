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
typedef  scalar_t__ u16 ;
struct clocksource {int dummy; } ;
typedef  scalar_t__ cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCFTIMER_TCN ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 scalar_t__ __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ mcftmr_cnt ; 

__attribute__((used)) static cycle_t mcftmr_read_clk(struct clocksource *cs)
{
	unsigned long flags;
	u32 cycles;
	u16 tcn;

	local_irq_save(flags);
	tcn = __raw_readw(TA(MCFTIMER_TCN));
	cycles = mcftmr_cnt;
	local_irq_restore(flags);

	return cycles + tcn;
}