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
struct group_irq {int dummy; } ;

/* Variables and functions */
#define  IRQ_GDMAGROUP 135 
#define  IRQ_GROUP0 134 
#define  IRQ_GROUP1 133 
#define  IRQ_I2CGROUP 132 
#define  IRQ_P2SGROUP 131 
#define  IRQ_SCGROUP 130 
#define  IRQ_T_INT_GROUP 129 
#define  IRQ_USBH 128 
 int /*<<< orphan*/  REG_AIC_MECR ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 struct group_irq group_gdma ; 
 struct group_irq group_i2c ; 
 int /*<<< orphan*/  group_irq_enable (struct group_irq*) ; 
 struct group_irq group_nirq0 ; 
 struct group_irq group_nirq1 ; 
 struct group_irq group_ottimer ; 
 struct group_irq group_ps2 ; 
 struct group_irq group_sc ; 
 struct group_irq group_usbh ; 

__attribute__((used)) static void nuc900_irq_unmask(unsigned int irq)
{
	struct group_irq *group_irq;

	group_irq = NULL;

	__raw_writel(1 << irq, REG_AIC_MECR);

	switch (irq) {
	case IRQ_GROUP0:
		group_irq = &group_nirq0;
		break;

	case IRQ_GROUP1:
		group_irq = &group_nirq1;
		break;

	case IRQ_USBH:
		group_irq = &group_usbh;
		break;

	case IRQ_T_INT_GROUP:
		group_irq = &group_ottimer;
		break;

	case IRQ_GDMAGROUP:
		group_irq = &group_gdma;
		break;

	case IRQ_SCGROUP:
		group_irq = &group_sc;
		break;

	case IRQ_I2CGROUP:
		group_irq = &group_i2c;
		break;

	case IRQ_P2SGROUP:
		group_irq = &group_ps2;
		break;
	}

	if (group_irq)
		group_irq_enable(group_irq);
}