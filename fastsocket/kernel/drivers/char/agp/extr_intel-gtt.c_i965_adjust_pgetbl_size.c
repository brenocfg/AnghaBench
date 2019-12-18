#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_2__ {scalar_t__ registers; } ;

/* Variables and functions */
 scalar_t__ I810_PGETBL_CTL ; 
 unsigned int I810_PGETBL_ENABLED ; 
 scalar_t__ I965_PGETBL_CTL2 ; 
 unsigned int I965_PGETBL_SIZE_MASK ; 
 TYPE_1__ intel_private ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void i965_adjust_pgetbl_size(unsigned int size_flag)
{
	u32 pgetbl_ctl, pgetbl_ctl2;

	/* ensure that ppgtt is disabled */
	pgetbl_ctl2 = readl(intel_private.registers+I965_PGETBL_CTL2);
	pgetbl_ctl2 &= ~I810_PGETBL_ENABLED;
	writel(pgetbl_ctl2, intel_private.registers+I965_PGETBL_CTL2);

	/* write the new ggtt size */
	pgetbl_ctl = readl(intel_private.registers+I810_PGETBL_CTL);
	pgetbl_ctl &= ~I965_PGETBL_SIZE_MASK;
	pgetbl_ctl |= size_flag;
	writel(pgetbl_ctl, intel_private.registers+I810_PGETBL_CTL);
}