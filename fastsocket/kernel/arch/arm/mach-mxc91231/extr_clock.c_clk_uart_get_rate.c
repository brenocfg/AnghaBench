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
typedef  unsigned long u32 ;
struct clk {int id; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAUDDIV ; 
 int /*<<< orphan*/  BUG () ; 
 unsigned long CRM_SMALL_DIVIDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXC_CRMAP_ACDER2 ; 
 int /*<<< orphan*/  MXC_CRMAP_APRA ; 
 int /*<<< orphan*/  UART3DIV ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_uart_get_rate(struct clk *clk)
{
	u32 div;

	switch (clk->id) {
	case 0:
	case 1:
		div = CRM_SMALL_DIVIDER(MXC_CRMAP_ACDER2, BAUDDIV);
		break;
	case 2:
		div = CRM_SMALL_DIVIDER(MXC_CRMAP_APRA, UART3DIV);
		break;
	default:
		BUG();
	}
	return clk_get_rate(clk->parent) / div;
}