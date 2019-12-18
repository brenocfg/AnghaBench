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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NO_IRQ ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 

int ibmebus_request_irq(u32 ist, irq_handler_t handler,
			unsigned long irq_flags, const char *devname,
			void *dev_id)
{
	unsigned int irq = irq_create_mapping(NULL, ist);

	if (irq == NO_IRQ)
		return -EINVAL;

	return request_irq(irq, handler, irq_flags, devname, dev_id);
}