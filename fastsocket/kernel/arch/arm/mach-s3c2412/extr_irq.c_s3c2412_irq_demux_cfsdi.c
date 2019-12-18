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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 unsigned int INTBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_S3C2412_CF ; 
 int /*<<< orphan*/  IRQ_S3C2412_SDI ; 
 int /*<<< orphan*/  S3C2410_INTSUBMSK ; 
 int /*<<< orphan*/  S3C2410_SUBSRCPND ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2412_irq_demux_cfsdi(unsigned int irq, struct irq_desc *desc)
{
	unsigned int subsrc, submsk;

	subsrc = __raw_readl(S3C2410_SUBSRCPND);
	submsk = __raw_readl(S3C2410_INTSUBMSK);

	subsrc  &= ~submsk;

	if (subsrc & INTBIT(IRQ_S3C2412_SDI))
		generic_handle_irq(IRQ_S3C2412_SDI);

	if (subsrc & INTBIT(IRQ_S3C2412_CF))
		generic_handle_irq(IRQ_S3C2412_CF);
}