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
struct i2c_cmd_arg {int /*<<< orphan*/  arg; int /*<<< orphan*/  cmd; } ;
struct i2c_client {TYPE_1__* driver; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* command ) (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct i2c_client* i2c_verify_client (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_cmd(struct device *dev, void *_arg)
{
	struct i2c_client	*client = i2c_verify_client(dev);
	struct i2c_cmd_arg	*arg = _arg;

	if (client && client->driver && client->driver->command)
		client->driver->command(client, arg->cmd, arg->arg);
	return 0;
}