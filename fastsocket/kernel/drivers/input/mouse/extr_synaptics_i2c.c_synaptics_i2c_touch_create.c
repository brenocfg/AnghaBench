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
struct synaptics_i2c {int /*<<< orphan*/  lock; int /*<<< orphan*/  dwork; int /*<<< orphan*/  scan_rate_param; int /*<<< orphan*/  no_decel_param; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct synaptics_i2c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_decel ; 
 int /*<<< orphan*/  scan_rate ; 
 int /*<<< orphan*/  set_scan_rate (struct synaptics_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synaptics_i2c_work_handler ; 

struct synaptics_i2c *synaptics_i2c_touch_create(struct i2c_client *client)
{
	struct synaptics_i2c *touch;

	touch = kzalloc(sizeof(struct synaptics_i2c), GFP_KERNEL);
	if (!touch)
		return NULL;

	touch->client = client;
	touch->no_decel_param = no_decel;
	touch->scan_rate_param = scan_rate;
	set_scan_rate(touch, scan_rate);
	INIT_DELAYED_WORK(&touch->dwork, synaptics_i2c_work_handler);
	spin_lock_init(&touch->lock);

	return touch;
}