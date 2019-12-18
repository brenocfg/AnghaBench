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
struct ld_usb {scalar_t__ ring_head; scalar_t__ ring_tail; int /*<<< orphan*/  interrupt_out_busy; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  intf; } ;
struct file {struct ld_usb* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ld_usb_poll(struct file *file, poll_table *wait)
{
	struct ld_usb *dev;
	unsigned int mask = 0;

	dev = file->private_data;

	if (!dev->intf)
		return POLLERR | POLLHUP;

	poll_wait(file, &dev->read_wait, wait);
	poll_wait(file, &dev->write_wait, wait);

	if (dev->ring_head != dev->ring_tail)
		mask |= POLLIN | POLLRDNORM;
	if (!dev->interrupt_out_busy)
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}