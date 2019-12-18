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

/* Variables and functions */
 scalar_t__ AVIC_INTDISNUM ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 scalar_t__ avic_base ; 

__attribute__((used)) static void mxc_mask_irq(unsigned int irq)
{
	__raw_writel(irq, avic_base + AVIC_INTDISNUM);
}