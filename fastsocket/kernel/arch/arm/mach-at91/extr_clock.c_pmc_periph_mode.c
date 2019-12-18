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
struct clk {int /*<<< orphan*/  pmc_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_PCDR ; 
 int /*<<< orphan*/  AT91_PMC_PCER ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmc_periph_mode(struct clk *clk, int is_on)
{
	if (is_on)
		at91_sys_write(AT91_PMC_PCER, clk->pmc_mask);
	else
		at91_sys_write(AT91_PMC_PCDR, clk->pmc_mask);
}