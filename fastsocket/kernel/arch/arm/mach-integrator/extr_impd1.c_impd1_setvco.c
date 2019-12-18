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
struct impd1_module {scalar_t__ base; struct clk* vcos; } ;
struct icst525_vco {int v; int r; int s; } ;
struct clk {struct impd1_module* data; } ;

/* Variables and functions */
 scalar_t__ IMPD1_LOCK ; 
 scalar_t__ IMPD1_OSC1 ; 
 scalar_t__ IMPD1_OSC2 ; 
 int /*<<< orphan*/  icst525_khz (int /*<<< orphan*/ *,struct icst525_vco) ; 
 int /*<<< orphan*/  impd1_vco_params ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void impd1_setvco(struct clk *clk, struct icst525_vco vco)
{
	struct impd1_module *impd1 = clk->data;
	int vconr = clk - impd1->vcos;
	u32 val;

	val = vco.v | (vco.r << 9) | (vco.s << 16);

	writel(0xa05f, impd1->base + IMPD1_LOCK);
	switch (vconr) {
	case 0:
		writel(val, impd1->base + IMPD1_OSC1);
		break;
	case 1:
		writel(val, impd1->base + IMPD1_OSC2);
		break;
	}
	writel(0, impd1->base + IMPD1_LOCK);

#ifdef DEBUG
	vco.v = val & 0x1ff;
	vco.r = (val >> 9) & 0x7f;
	vco.s = (val >> 16) & 7;

	pr_debug("IM-PD1: VCO%d clock is %ld kHz\n",
		 vconr, icst525_khz(&impd1_vco_params, vco));
#endif
}