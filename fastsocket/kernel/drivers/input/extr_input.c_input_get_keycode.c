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
struct input_dev {int (* getkeycode ) (struct input_dev*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct input_dev*,int,int*) ; 

int input_get_keycode(struct input_dev *dev, int scancode, int *keycode)
{
	if (scancode < 0)
		return -EINVAL;

	return dev->getkeycode(dev, scancode, keycode);
}