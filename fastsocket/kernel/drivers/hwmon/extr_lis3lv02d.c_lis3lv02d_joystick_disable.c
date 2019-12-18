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
struct TYPE_2__ {int /*<<< orphan*/ * idev; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ *) ; 
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  lis3lv02d_misc_device ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

void lis3lv02d_joystick_disable(void)
{
	if (!lis3_dev.idev)
		return;

	if (lis3_dev.irq)
		misc_deregister(&lis3lv02d_misc_device);
	input_unregister_polled_device(lis3_dev.idev);
	lis3_dev.idev = NULL;
}