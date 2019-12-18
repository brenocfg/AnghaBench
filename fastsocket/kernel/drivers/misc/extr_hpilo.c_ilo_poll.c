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
struct file {struct ccb_data* private_data; } ;
struct ccb {int dummy; } ;
struct ccb_data {int /*<<< orphan*/  ilo_hw; int /*<<< orphan*/  ccb_waitq; struct ccb driver_ccb; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ ilo_pkt_recv (int /*<<< orphan*/ ,struct ccb*) ; 
 scalar_t__ is_channel_reset (struct ccb*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ilo_poll(struct file *fp, poll_table *wait)
{
	struct ccb_data *data = fp->private_data;
	struct ccb *driver_ccb = &data->driver_ccb;

	poll_wait(fp, &data->ccb_waitq, wait);

	if (is_channel_reset(driver_ccb))
		return POLLERR;
	else if (ilo_pkt_recv(data->ilo_hw, driver_ccb))
		return POLLIN | POLLRDNORM;

	return 0;
}