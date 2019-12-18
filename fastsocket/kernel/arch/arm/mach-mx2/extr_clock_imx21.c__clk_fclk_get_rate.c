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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int CCM_CSCR_PRESC_MASK ; 
 int CCM_CSCR_PRESC_OFFSET ; 
 int CSCR () ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long _clk_fclk_get_rate(struct clk *clk)
{
	unsigned long parent_rate;
	u32 div;

	div = (CSCR() & CCM_CSCR_PRESC_MASK) >> CCM_CSCR_PRESC_OFFSET;
	parent_rate = clk_get_rate(clk->parent);

	return parent_rate / (div+1);
}