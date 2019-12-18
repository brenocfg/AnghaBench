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
typedef  int u32 ;
struct clk {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  MXC_CRMAP_APRB ; 
 int MXC_CRMAP_APRB_SDHC1_ISEL_MASK ; 
 int MXC_CRMAP_APRB_SDHC1_ISEL_OFFSET ; 
 int MXC_CRMAP_APRB_SDHC2_ISEL_MASK ; 
 int MXC_CRMAP_APRB_SDHC2_ISEL_OFFSET ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 struct clk ckih_clk ; 
 struct clk ckih_x2_clk ; 
 struct clk usb_clk ; 

__attribute__((used)) static struct clk *clk_sdhc_parent(struct clk *clk)
{
	u32 aprb;
	u8 sel;
	u32 mask;
	int offset;

	aprb = __raw_readl(MXC_CRMAP_APRB);

	switch (clk->id) {
	case 0:
		mask = MXC_CRMAP_APRB_SDHC1_ISEL_MASK;
		offset = MXC_CRMAP_APRB_SDHC1_ISEL_OFFSET;
		break;
	case 1:
		mask = MXC_CRMAP_APRB_SDHC2_ISEL_MASK;
		offset = MXC_CRMAP_APRB_SDHC2_ISEL_OFFSET;
		break;
	default:
		BUG();
	}
	sel = (aprb & mask) >> offset;

	switch (sel) {
	case 0:
		return &ckih_clk;
	case 1:
		return &ckih_x2_clk;
	}
	return &usb_clk;
}