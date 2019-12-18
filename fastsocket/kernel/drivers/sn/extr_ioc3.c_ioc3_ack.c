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
struct ioc3_submodule {unsigned int irq_mask; } ;
struct ioc3_driver_data {TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  sio_ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 

void ioc3_ack(struct ioc3_submodule *is, struct ioc3_driver_data *idd,
				unsigned int irqs)
{
	writel(irqs & is->irq_mask, &idd->vma->sio_ir);
}