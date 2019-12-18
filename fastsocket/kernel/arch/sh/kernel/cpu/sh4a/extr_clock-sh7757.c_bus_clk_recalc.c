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
struct clk {int rate; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int* bfc_divisors ; 
 int ctrl_inl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bus_clk_recalc(struct clk *clk)
{
	int idx = (ctrl_inl(FRQCR) >> 8) & 0x0000000f;
	clk->rate = clk->parent->rate / bfc_divisors[idx];
}