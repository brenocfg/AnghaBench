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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int activate_fd (unsigned int,int,int,void*) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 

int um_request_irq(unsigned int irq, int fd, int type,
		   irq_handler_t handler,
		   unsigned long irqflags, const char * devname,
		   void *dev_id)
{
	int err;

	if (fd != -1) {
		err = activate_fd(irq, fd, type, dev_id);
		if (err)
			return err;
	}

	return request_irq(irq, handler, irqflags, devname, dev_id);
}