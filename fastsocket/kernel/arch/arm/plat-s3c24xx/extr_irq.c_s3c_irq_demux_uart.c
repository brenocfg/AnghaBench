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
 unsigned int IRQ_S3CUART_RX0 ; 
 int /*<<< orphan*/  S3C2410_INTSUBMSK ; 
 int /*<<< orphan*/  S3C2410_SUBSRCPND ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int /*<<< orphan*/  irqdbf2 (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void s3c_irq_demux_uart(unsigned int start)
{
	unsigned int subsrc, submsk;
	unsigned int offset = start - IRQ_S3CUART_RX0;

	/* read the current pending interrupts, and the mask
	 * for what it is available */

	subsrc = __raw_readl(S3C2410_SUBSRCPND);
	submsk = __raw_readl(S3C2410_INTSUBMSK);

	irqdbf2("s3c_irq_demux_uart: start=%d (%d), subsrc=0x%08x,0x%08x\n",
		start, offset, subsrc, submsk);

	subsrc &= ~submsk;
	subsrc >>= offset;
	subsrc &= 7;

	if (subsrc != 0) {
		if (subsrc & 1)
			generic_handle_irq(start);

		if (subsrc & 2)
			generic_handle_irq(start+1);

		if (subsrc & 4)
			generic_handle_irq(start+2);
	}
}