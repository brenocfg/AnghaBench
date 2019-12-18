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
struct file {int /*<<< orphan*/  f_flags; struct ep_data* private_data; } ;
struct ep_data {int /*<<< orphan*/  lock; TYPE_1__* dev; int /*<<< orphan*/ * ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTTY ; 
#define  GADGETFS_CLEAR_HALT 130 
#define  GADGETFS_FIFO_FLUSH 129 
#define  GADGETFS_FIFO_STATUS 128 
 int get_ready_ep (int /*<<< orphan*/ ,struct ep_data*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int usb_ep_clear_halt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_fifo_flush (int /*<<< orphan*/ *) ; 
 int usb_ep_fifo_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ep_ioctl(struct file *fd, unsigned code, unsigned long value)
{
	struct ep_data		*data = fd->private_data;
	int			status;

	if ((status = get_ready_ep (fd->f_flags, data)) < 0)
		return status;

	spin_lock_irq (&data->dev->lock);
	if (likely (data->ep != NULL)) {
		switch (code) {
		case GADGETFS_FIFO_STATUS:
			status = usb_ep_fifo_status (data->ep);
			break;
		case GADGETFS_FIFO_FLUSH:
			usb_ep_fifo_flush (data->ep);
			break;
		case GADGETFS_CLEAR_HALT:
			status = usb_ep_clear_halt (data->ep);
			break;
		default:
			status = -ENOTTY;
		}
	} else
		status = -ENODEV;
	spin_unlock_irq (&data->dev->lock);
	up (&data->lock);
	return status;
}