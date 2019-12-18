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
struct cx231xx {int state; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  cx231xx_errdev (char*) ; 

__attribute__((used)) static int check_dev(struct cx231xx *dev)
{
	if (dev->state & DEV_DISCONNECTED) {
		cx231xx_errdev("v4l2 ioctl: device not present\n");
		return -ENODEV;
	}

	if (dev->state & DEV_MISCONFIGURED) {
		cx231xx_errdev("v4l2 ioctl: device is misconfigured; "
			       "close and open it again\n");
		return -EIO;
	}
	return 0;
}