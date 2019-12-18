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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_PIC_IRQMASK (int) ; 
 int /*<<< orphan*/  IRQ_HOST_MAP_LINEAR ; 
 scalar_t__ NO_IRQ ; 
 int SOCRATES_FPGA_IRQ_MASK ; 
 int /*<<< orphan*/  SOCRATES_FPGA_NUM_IRQS ; 
 int /*<<< orphan*/ * irq_alloc_host (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  set_irq_chained_handler (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* socrates_fpga_irqs ; 
 int /*<<< orphan*/  socrates_fpga_pic_cascade ; 
 int /*<<< orphan*/  socrates_fpga_pic_host_ops ; 
 int /*<<< orphan*/  socrates_fpga_pic_iobase ; 
 int /*<<< orphan*/ * socrates_fpga_pic_irq_host ; 
 int /*<<< orphan*/  socrates_fpga_pic_lock ; 
 int /*<<< orphan*/  socrates_fpga_pic_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void socrates_fpga_pic_init(struct device_node *pic)
{
	unsigned long flags;
	int i;

	/* Setup an irq_host structure */
	socrates_fpga_pic_irq_host = irq_alloc_host(pic, IRQ_HOST_MAP_LINEAR,
			SOCRATES_FPGA_NUM_IRQS,	&socrates_fpga_pic_host_ops,
			SOCRATES_FPGA_NUM_IRQS);
	if (socrates_fpga_pic_irq_host == NULL) {
		pr_err("FPGA PIC: Unable to allocate host\n");
		return;
	}

	for (i = 0; i < 3; i++) {
		socrates_fpga_irqs[i] = irq_of_parse_and_map(pic, i);
		if (socrates_fpga_irqs[i] == NO_IRQ) {
			pr_warning("FPGA PIC: can't get irq%d.\n", i);
			continue;
		}
		set_irq_chained_handler(socrates_fpga_irqs[i],
				socrates_fpga_pic_cascade);
	}

	socrates_fpga_pic_iobase = of_iomap(pic, 0);

	spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	socrates_fpga_pic_write(FPGA_PIC_IRQMASK(0),
			SOCRATES_FPGA_IRQ_MASK << 16);
	socrates_fpga_pic_write(FPGA_PIC_IRQMASK(1),
			SOCRATES_FPGA_IRQ_MASK << 16);
	socrates_fpga_pic_write(FPGA_PIC_IRQMASK(2),
			SOCRATES_FPGA_IRQ_MASK << 16);
	spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);

	pr_info("FPGA PIC: Setting up Socrates FPGA PIC\n");
}