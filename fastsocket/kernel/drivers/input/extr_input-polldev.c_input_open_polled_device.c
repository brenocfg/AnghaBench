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
struct input_polled_dev {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  work; int /*<<< orphan*/  (* flush ) (struct input_polled_dev*) ;} ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct input_polled_dev* input_get_drvdata (struct input_dev*) ; 
 int input_polldev_start_workqueue () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  polldev_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct input_polled_dev*) ; 

__attribute__((used)) static int input_open_polled_device(struct input_dev *input)
{
	struct input_polled_dev *dev = input_get_drvdata(input);
	int error;

	error = input_polldev_start_workqueue();
	if (error)
		return error;

	if (dev->flush)
		dev->flush(dev);

	queue_delayed_work(polldev_wq, &dev->work,
			   msecs_to_jiffies(dev->poll_interval));

	return 0;
}