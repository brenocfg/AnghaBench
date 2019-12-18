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
struct iowarrior {int /*<<< orphan*/  write_busy; int /*<<< orphan*/  present; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; } ;
struct file {struct iowarrior* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ MAX_WRITES_IN_FLIGHT ; 
 int POLLERR ; 
 int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_index (struct iowarrior*) ; 

__attribute__((used)) static unsigned iowarrior_poll(struct file *file, poll_table * wait)
{
	struct iowarrior *dev = file->private_data;
	unsigned int mask = 0;

	if (!dev->present)
		return POLLERR | POLLHUP;

	poll_wait(file, &dev->read_wait, wait);
	poll_wait(file, &dev->write_wait, wait);

	if (!dev->present)
		return POLLERR | POLLHUP;

	if (read_index(dev) != -1)
		mask |= POLLIN | POLLRDNORM;

	if (atomic_read(&dev->write_busy) < MAX_WRITES_IN_FLIGHT)
		mask |= POLLOUT | POLLWRNORM;
	return mask;
}