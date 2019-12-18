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
struct file {struct channel_info* private_data; } ;
struct channel_info {scalar_t__ dir; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIR_RX ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ poch_channel_available (struct channel_info*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int poch_poll(struct file *filp, poll_table *pt)
{
	struct channel_info *channel = filp->private_data;
	unsigned int ret = 0;

	poll_wait(filp, &channel->wq, pt);

	if (poch_channel_available(channel)) {
		if (channel->dir == CHANNEL_DIR_RX)
			ret = POLLIN | POLLRDNORM;
		else
			ret = POLLOUT | POLLWRNORM;
	}

	return ret;
}