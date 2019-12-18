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
 int PFC_MSK ; 
 int PFC_POS ; 
 int ctrl_inl (int /*<<< orphan*/ ) ; 
 unsigned long* pfc_divisors ; 

__attribute__((used)) static unsigned long module_clk_recalc(struct clk *clk)
{
	int idx = ((ctrl_inl(FRQCR) >> PFC_POS) & PFC_MSK);
	return clk->parent->rate / pfc_divisors[idx];
}