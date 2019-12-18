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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_CCR ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER ; 
 int U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK ; 
 scalar_t__ U300_SYSCON_VBASE ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  syscon_clkreg_lock ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

void syscon_clk_rate_set_cpuclk(unsigned long rate)
{
	u16 val;
	unsigned long iflags;

	switch (rate) {
	case 13000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER;
		break;
	case 52000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE;
		break;
	case 104000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH;
		break;
	case 208000000:
		val = U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST;
		break;
	default:
		return;
	}
	spin_lock_irqsave(&syscon_clkreg_lock, iflags);
	val |= readw(U300_SYSCON_VBASE + U300_SYSCON_CCR) &
		~U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK ;
	writew(val, U300_SYSCON_VBASE + U300_SYSCON_CCR);
	spin_unlock_irqrestore(&syscon_clkreg_lock, iflags);
}