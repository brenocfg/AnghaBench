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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  S3C64XX_EINT0MASK ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eint_irq_to_bit (unsigned int) ; 

__attribute__((used)) static inline void s3c_irq_eint_mask(unsigned int irq)
{
	u32 mask;

	mask = __raw_readl(S3C64XX_EINT0MASK);
	mask |= eint_irq_to_bit(irq);
	__raw_writel(mask, S3C64XX_EINT0MASK);
}