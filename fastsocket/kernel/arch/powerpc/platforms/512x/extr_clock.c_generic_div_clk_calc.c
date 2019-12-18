#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk {int div_shift; int rate; TYPE_1__* parent; } ;
struct TYPE_4__ {int scfr1; } ;
struct TYPE_3__ {int rate; } ;

/* Variables and functions */
 TYPE_2__* clockctl ; 

__attribute__((used)) static void generic_div_clk_calc(struct clk *clk)
{
	int div = (clockctl->scfr1 >> clk->div_shift) & 0x7;

	clk->rate = clk->parent->rate / div;
}