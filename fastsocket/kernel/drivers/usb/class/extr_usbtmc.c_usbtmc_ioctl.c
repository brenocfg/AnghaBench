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
struct usbtmc_device_data {int /*<<< orphan*/  io_mutex; scalar_t__ zombie; } ;
struct file {struct usbtmc_device_data* private_data; } ;

/* Variables and functions */
 int EBADRQC ; 
 int ENODEV ; 
#define  USBTMC_IOCTL_ABORT_BULK_IN 133 
#define  USBTMC_IOCTL_ABORT_BULK_OUT 132 
#define  USBTMC_IOCTL_CLEAR 131 
#define  USBTMC_IOCTL_CLEAR_IN_HALT 130 
#define  USBTMC_IOCTL_CLEAR_OUT_HALT 129 
#define  USBTMC_IOCTL_INDICATOR_PULSE 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usbtmc_ioctl_abort_bulk_in (struct usbtmc_device_data*) ; 
 int usbtmc_ioctl_abort_bulk_out (struct usbtmc_device_data*) ; 
 int usbtmc_ioctl_clear (struct usbtmc_device_data*) ; 
 int usbtmc_ioctl_clear_in_halt (struct usbtmc_device_data*) ; 
 int usbtmc_ioctl_clear_out_halt (struct usbtmc_device_data*) ; 
 int usbtmc_ioctl_indicator_pulse (struct usbtmc_device_data*) ; 

__attribute__((used)) static long usbtmc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct usbtmc_device_data *data;
	int retval = -EBADRQC;

	data = file->private_data;
	mutex_lock(&data->io_mutex);
	if (data->zombie) {
		retval = -ENODEV;
		goto skip_io_on_zombie;
	}

	switch (cmd) {
	case USBTMC_IOCTL_CLEAR_OUT_HALT:
		retval = usbtmc_ioctl_clear_out_halt(data);
		break;

	case USBTMC_IOCTL_CLEAR_IN_HALT:
		retval = usbtmc_ioctl_clear_in_halt(data);
		break;

	case USBTMC_IOCTL_INDICATOR_PULSE:
		retval = usbtmc_ioctl_indicator_pulse(data);
		break;

	case USBTMC_IOCTL_CLEAR:
		retval = usbtmc_ioctl_clear(data);
		break;

	case USBTMC_IOCTL_ABORT_BULK_OUT:
		retval = usbtmc_ioctl_abort_bulk_out(data);
		break;

	case USBTMC_IOCTL_ABORT_BULK_IN:
		retval = usbtmc_ioctl_abort_bulk_in(data);
		break;
	}

skip_io_on_zombie:
	mutex_unlock(&data->io_mutex);
	return retval;
}