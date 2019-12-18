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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_CSCR ; 
 int CCM_CSCR_USB_MASK ; 
 int CCM_CSCR_USB_OFFSET ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk48m_get_rate(struct clk *clk)
{
	return clk_get_rate(clk->parent) / (((__raw_readl(CCM_CSCR) &
			CCM_CSCR_USB_MASK) >> CCM_CSCR_USB_OFFSET) + 1);
}