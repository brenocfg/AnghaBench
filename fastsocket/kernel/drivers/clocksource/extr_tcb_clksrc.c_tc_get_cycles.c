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
typedef  int u32 ;
struct clocksource {int dummy; } ;
typedef  int cycle_t ;

/* Variables and functions */
 scalar_t__ ATMEL_TC_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CV ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 scalar_t__ tcaddr ; 

__attribute__((used)) static cycle_t tc_get_cycles(struct clocksource *cs)
{
	unsigned long	flags;
	u32		lower, upper;

	raw_local_irq_save(flags);
	do {
		upper = __raw_readl(tcaddr + ATMEL_TC_REG(1, CV));
		lower = __raw_readl(tcaddr + ATMEL_TC_REG(0, CV));
	} while (upper != __raw_readl(tcaddr + ATMEL_TC_REG(1, CV)));

	raw_local_irq_restore(flags);
	return (upper << 16) | lower;
}