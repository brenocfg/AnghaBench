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
struct clk {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pfc_divisors ; 

__attribute__((used)) static void master_clk_init(struct clk *clk)
{
	int frqcr = ctrl_inw(FRQCR);
	int idx = ((frqcr & 0x2000) >> 11) | (frqcr & 0x0003);

	clk->rate *= pfc_divisors[idx];
}