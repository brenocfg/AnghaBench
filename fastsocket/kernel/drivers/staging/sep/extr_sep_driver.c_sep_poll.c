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
struct sep_device {unsigned long send_ct; unsigned long reply_ct; scalar_t__ shared_addr; } ;
struct file {struct sep_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  HW_HOST_SEP_HOST_GPR2_REG_ADDR ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ SEP_DRIVER_MESSAGE_SHARED_AREA_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,...) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sep_event ; 
 unsigned long sep_read_reg (struct sep_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int sep_poll(struct file *filp, poll_table * wait)
{
	unsigned long count;
	unsigned int mask = 0;
	unsigned long retval = 0;	/* flow id */
	struct sep_device *sep = filp->private_data;

	dbg("---------->SEP Driver poll: start\n");


#if SEP_DRIVER_POLLING_MODE

	while (sep->send_ct != (retval & 0x7FFFFFFF)) {
		retval = sep_read_reg(sep, HW_HOST_SEP_HOST_GPR2_REG_ADDR);

		for (count = 0; count < 10 * 4; count += 4)
			edbg("Poll Debug Word %lu of the message is %lu\n", count, *((unsigned long *) (sep->shared_addr + SEP_DRIVER_MESSAGE_SHARED_AREA_SIZE_IN_BYTES + count)));
	}

	sep->reply_ct++;
#else
	/* add the event to the polling wait table */
	poll_wait(filp, &sep_event, wait);

#endif

	edbg("sep->send_ct is %lu\n", sep->send_ct);
	edbg("sep->reply_ct is %lu\n", sep->reply_ct);

	/* check if the data is ready */
	if (sep->send_ct == sep->reply_ct) {
		for (count = 0; count < 12 * 4; count += 4)
			edbg("Sep Mesg Word %lu of the message is %lu\n", count, *((unsigned long *) (sep->shared_addr + count)));

		for (count = 0; count < 10 * 4; count += 4)
			edbg("Debug Data Word %lu of the message is %lu\n", count, *((unsigned long *) (sep->shared_addr + 0x1800 + count)));

		retval = sep_read_reg(sep, HW_HOST_SEP_HOST_GPR2_REG_ADDR);
		edbg("retval is %lu\n", retval);
		/* check if the this is sep reply or request */
		if (retval >> 31) {
			edbg("SEP Driver: sep request in\n");
			/* request */
			mask |= POLLOUT | POLLWRNORM;
		} else {
			edbg("SEP Driver: sep reply in\n");
			mask |= POLLIN | POLLRDNORM;
		}
	}
	dbg("SEP Driver:<-------- poll exit\n");
	return mask;
}