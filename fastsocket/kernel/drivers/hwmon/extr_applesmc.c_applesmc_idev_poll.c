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
struct input_polled_dev {struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  SENSOR_X ; 
 int /*<<< orphan*/  SENSOR_Y ; 
 int /*<<< orphan*/  applesmc_lock ; 
 scalar_t__ applesmc_read_motion_sensor (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rest_x ; 
 scalar_t__ rest_y ; 

__attribute__((used)) static void applesmc_idev_poll(struct input_polled_dev *dev)
{
	struct input_dev *idev = dev->input;
	s16 x, y;

	mutex_lock(&applesmc_lock);

	if (applesmc_read_motion_sensor(SENSOR_X, &x))
		goto out;
	if (applesmc_read_motion_sensor(SENSOR_Y, &y))
		goto out;

	x = -x;
	input_report_abs(idev, ABS_X, x - rest_x);
	input_report_abs(idev, ABS_Y, y - rest_y);
	input_sync(idev);

out:
	mutex_unlock(&applesmc_lock);
}