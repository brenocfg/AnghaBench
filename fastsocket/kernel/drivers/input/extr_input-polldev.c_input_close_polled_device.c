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
struct input_polled_dev {int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct input_polled_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  input_polldev_stop_workqueue () ; 

__attribute__((used)) static void input_close_polled_device(struct input_dev *input)
{
	struct input_polled_dev *dev = input_get_drvdata(input);

	cancel_delayed_work_sync(&dev->work);
	input_polldev_stop_workqueue();
}