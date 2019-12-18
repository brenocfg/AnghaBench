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
 int /*<<< orphan*/  CCM_PCDR0 ; 
 scalar_t__ CHIP_REV_2_0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ mx27_revision () ; 

__attribute__((used)) static unsigned long get_rate_vpu(struct clk *clk)
{
	unsigned long vpu_pdf;
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	if (mx27_revision() >= CHIP_REV_2_0) {
		vpu_pdf = (__raw_readl(CCM_PCDR0) >> 10) & 0x3f;
		vpu_pdf += 4;
	} else {
		vpu_pdf = (__raw_readl(CCM_PCDR0) >> 8) & 0xf;
		vpu_pdf = (vpu_pdf < 2) ? 124 : vpu_pdf;
	}

	return 2UL * parent_rate / vpu_pdf;
}