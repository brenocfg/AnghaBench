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
struct joydev_client {struct joydev* joydev; } ;
struct joydev {scalar_t__ exist; int /*<<< orphan*/  wait; } ;
struct file {struct joydev_client* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ joydev_data_pending (struct joydev_client*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int joydev_poll(struct file *file, poll_table *wait)
{
	struct joydev_client *client = file->private_data;
	struct joydev *joydev = client->joydev;

	poll_wait(file, &joydev->wait, wait);
	return (joydev_data_pending(client) ? (POLLIN | POLLRDNORM) : 0) |
		(joydev->exist ?  0 : (POLLHUP | POLLERR));
}