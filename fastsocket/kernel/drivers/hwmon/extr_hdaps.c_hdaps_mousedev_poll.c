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

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  HDAPS_PORT_XPOS ; 
 int /*<<< orphan*/  HDAPS_PORT_YPOS ; 
 scalar_t__ __hdaps_read_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  hdaps_mtx ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rest_x ; 
 scalar_t__ rest_y ; 

__attribute__((used)) static void hdaps_mousedev_poll(struct input_polled_dev *dev)
{
	struct input_dev *input_dev = dev->input;
	int x, y;

	mutex_lock(&hdaps_mtx);

	if (__hdaps_read_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &x, &y))
		goto out;

	input_report_abs(input_dev, ABS_X, x - rest_x);
	input_report_abs(input_dev, ABS_Y, y - rest_y);
	input_sync(input_dev);

out:
	mutex_unlock(&hdaps_mtx);
}