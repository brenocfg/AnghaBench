#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {TYPE_1__** interrupts; } ;
struct TYPE_3__ {int line_number; unsigned int irq; struct iio_dev* dev_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* iio_allocate_interrupt () ; 
 int /*<<< orphan*/  iio_interrupt_handler ; 
 int request_irq (unsigned int,int /*<<< orphan*/ *,unsigned long,char const*,TYPE_1__*) ; 

int iio_register_interrupt_line(unsigned int irq,
				struct iio_dev *dev_info,
				int line_number,
				unsigned long type,
				const char *name)
{
	int ret;

	dev_info->interrupts[line_number] = iio_allocate_interrupt();
	if (dev_info->interrupts[line_number] == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	dev_info->interrupts[line_number]->line_number = line_number;
	dev_info->interrupts[line_number]->irq = irq;
	dev_info->interrupts[line_number]->dev_info = dev_info;

	/* Possibly only request on demand?
	 * Can see this may complicate the handling of interrupts.
	 * However, with this approach we might end up handling lots of
	 * events no-one cares about.*/
	ret = request_irq(irq,
			  &iio_interrupt_handler,
			  type,
			  name,
			  dev_info->interrupts[line_number]);

error_ret:
	return ret;
}