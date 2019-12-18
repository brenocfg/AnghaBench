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
 int /*<<< orphan*/  MXC_CCM_PDR1_SSI1_PODF_MASK ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_SSI1_PODF_OFFSET ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_SSI1_PRE_PODF_MASK ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_SSI1_PRE_PODF_OFFSET ; 
 unsigned long PDR1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ssi1_get_rate(struct clk *clk)
{
	unsigned long ssi1_pdf, ssi1_prepdf;

	ssi1_pdf = PDR1(MXC_CCM_PDR1_SSI1_PODF_MASK,
			MXC_CCM_PDR1_SSI1_PODF_OFFSET);
	ssi1_prepdf = PDR1(MXC_CCM_PDR1_SSI1_PRE_PODF_MASK,
			   MXC_CCM_PDR1_SSI1_PRE_PODF_OFFSET);
	return clk_get_rate(clk->parent) / (ssi1_prepdf + 1) / (ssi1_pdf + 1);
}