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
struct i2c_client {int dummy; } ;
struct IR_i2c {int /*<<< orphan*/  rc; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct IR_i2c* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct IR_i2c*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_remove(struct i2c_client *client)
{
	struct IR_i2c *ir = i2c_get_clientdata(client);

	/* kill outstanding polls */
	cancel_delayed_work_sync(&ir->work);

	/* unregister device */
	rc_unregister_device(ir->rc);

	/* free memory */
	kfree(ir);
	return 0;
}