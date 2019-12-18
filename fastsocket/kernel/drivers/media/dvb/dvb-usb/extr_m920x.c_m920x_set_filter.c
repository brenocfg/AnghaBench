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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M9206_FILTER ; 
 int m920x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int m920x_set_filter(struct dvb_usb_device *d, int type, int idx, int pid)
{
	int ret = 0;

	if (pid >= 0x8000)
		return -EINVAL;

	pid |= 0x8000;

	if ((ret = m920x_write(d->udev, M9206_FILTER, pid, (type << 8) | (idx * 4) )) != 0)
		return ret;

	if ((ret = m920x_write(d->udev, M9206_FILTER, 0, (type << 8) | (idx * 4) )) != 0)
		return ret;

	return ret;
}