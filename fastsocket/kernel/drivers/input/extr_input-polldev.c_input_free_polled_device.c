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
struct input_polled_dev {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct input_polled_dev*) ; 

void input_free_polled_device(struct input_polled_dev *dev)
{
	if (dev) {
		input_free_device(dev->input);
		kfree(dev);
	}
}