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
struct input_dev {int dummy; } ;
struct cm109_dev {int /*<<< orphan*/  intf; int /*<<< orphan*/  pm_mutex; scalar_t__ open; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_stop_traffic (struct cm109_dev*) ; 
 struct cm109_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm109_input_close(struct input_dev *idev)
{
	struct cm109_dev *dev = input_get_drvdata(idev);

	mutex_lock(&dev->pm_mutex);

	/*
	 * Once we are here event delivery is stopped so we
	 * don't need to worry about someone starting buzzer
	 * again
	 */
	cm109_stop_traffic(dev);
	dev->open = 0;

	mutex_unlock(&dev->pm_mutex);

	usb_autopm_put_interface(dev->intf);
}