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
struct bcm5974 {int opened; int /*<<< orphan*/  intf; int /*<<< orphan*/  pm_mutex; } ;

/* Variables and functions */
 int bcm5974_start_traffic (struct bcm5974*) ; 
 struct bcm5974* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm5974_open(struct input_dev *input)
{
	struct bcm5974 *dev = input_get_drvdata(input);
	int error;

	error = usb_autopm_get_interface(dev->intf);
	if (error)
		return error;

	mutex_lock(&dev->pm_mutex);

	error = bcm5974_start_traffic(dev);
	if (!error)
		dev->opened = 1;

	mutex_unlock(&dev->pm_mutex);

	if (error)
		usb_autopm_put_interface(dev->intf);

	return error;
}