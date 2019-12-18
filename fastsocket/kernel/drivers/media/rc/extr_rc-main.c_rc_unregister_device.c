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
struct rc_dev {scalar_t__ driver_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  rc_map; int /*<<< orphan*/ * input_dev; int /*<<< orphan*/  timer_keyup; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_dprintk (int,char*) ; 
 scalar_t__ RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_free_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_raw_event_unregister (struct rc_dev*) ; 

void rc_unregister_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	del_timer_sync(&dev->timer_keyup);

	if (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_event_unregister(dev);

	input_unregister_device(dev->input_dev);
	dev->input_dev = NULL;

	ir_free_table(&dev->rc_map);
	IR_dprintk(1, "Freed keycode table\n");

	device_unregister(&dev->dev);
}