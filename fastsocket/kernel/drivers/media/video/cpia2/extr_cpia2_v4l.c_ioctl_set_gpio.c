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
struct camera_data {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int cpia2_set_gpio (struct camera_data*,unsigned char) ; 

__attribute__((used)) static int ioctl_set_gpio(void *arg, struct camera_data *cam)
{
	__u32 gpio_val;

	gpio_val = *(__u32*) arg;

	if (gpio_val &~ 0xFFU)
		return -EINVAL;

	return cpia2_set_gpio(cam, (unsigned char)gpio_val);
}