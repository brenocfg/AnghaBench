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
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 unsigned long* ifc_divisors ; 

__attribute__((used)) static unsigned long cpu_clk_recalc(struct clk *clk)
{
	int frqcr = ctrl_inw(FRQCR);
	int idx = ((frqcr & 0x4000) >> 12) | ((frqcr & 0x000c) >> 2);

	return clk->parent->rate / ifc_divisors[idx];
}