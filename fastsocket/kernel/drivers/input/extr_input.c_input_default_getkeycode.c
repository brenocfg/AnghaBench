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
struct input_dev {int keycodemax; int /*<<< orphan*/  keycodesize; } ;

/* Variables and functions */
 int EINVAL ; 
 int input_fetch_keycode (struct input_dev*,int) ; 

__attribute__((used)) static int input_default_getkeycode(struct input_dev *dev,
				    int scancode, int *keycode)
{
	if (!dev->keycodesize)
		return -EINVAL;

	if (scancode >= dev->keycodemax)
		return -EINVAL;

	*keycode = input_fetch_keycode(dev, scancode);

	return 0;
}