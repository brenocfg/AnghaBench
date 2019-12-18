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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_PIC_IRQMASK (int) ; 
 unsigned int NO_IRQ ; 
 int SOCRATES_FPGA_NUM_IRQS ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* socrates_fpga_irqs ; 
 int /*<<< orphan*/  socrates_fpga_pic_irq_host ; 
 int /*<<< orphan*/  socrates_fpga_pic_lock ; 
 int socrates_fpga_pic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned int socrates_fpga_pic_get_irq(unsigned int irq)
{
	uint32_t cause;
	unsigned long flags;
	int i;

	/* Check irq line routed to the MPIC */
	for (i = 0; i < 3; i++) {
		if (irq == socrates_fpga_irqs[i])
			break;
	}
	if (i == 3)
		return NO_IRQ;

	spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	cause = socrates_fpga_pic_read(FPGA_PIC_IRQMASK(i));
	spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
	for (i = SOCRATES_FPGA_NUM_IRQS - 1; i >= 0; i--) {
		if (cause >> (i + 16))
			break;
	}
	return irq_linear_revmap(socrates_fpga_pic_irq_host,
			(irq_hw_number_t)i);
}