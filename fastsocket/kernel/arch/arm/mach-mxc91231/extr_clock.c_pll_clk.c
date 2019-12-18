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
typedef  int u8 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct clk dsp_pll_clk ; 
 struct clk mcu_pll_clk ; 
 struct clk usb_pll_clk ; 

__attribute__((used)) static struct clk *pll_clk(u8 sel)
{
	switch (sel) {
	case 0:
		return &mcu_pll_clk;
	case 1:
		return &dsp_pll_clk;
	case 2:
		return &usb_pll_clk;
	}
	BUG();
}