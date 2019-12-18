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
 int /*<<< orphan*/  S3C2410_INTSUBMSK ; 
 unsigned int S3C2410_IRQSUB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2410_SUBSRCPND ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static inline void s3c2443_irq_demux(unsigned int irq, unsigned int len)
{
	unsigned int subsrc, submsk;
	unsigned int end;

	/* read the current pending interrupts, and the mask
	 * for what it is available */

	subsrc = __raw_readl(S3C2410_SUBSRCPND);
	submsk = __raw_readl(S3C2410_INTSUBMSK);

	subsrc  &= ~submsk;
	subsrc >>= (irq - S3C2410_IRQSUB(0));
	subsrc  &= (1 << len)-1;

	end = len + irq;

	for (; irq < end && subsrc; irq++) {
		if (subsrc & 1)
			generic_handle_irq(irq);

		subsrc >>= 1;
	}
}