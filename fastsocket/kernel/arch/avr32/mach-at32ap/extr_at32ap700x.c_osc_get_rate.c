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
struct clk {size_t index; } ;

/* Variables and functions */
 unsigned long* at32_board_osc_rates ; 

__attribute__((used)) static unsigned long osc_get_rate(struct clk *clk)
{
	return at32_board_osc_rates[clk->index];
}