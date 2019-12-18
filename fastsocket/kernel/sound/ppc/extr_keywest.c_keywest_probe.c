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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keywest_ctx ; 

__attribute__((used)) static int keywest_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	i2c_set_clientdata(client, keywest_ctx);
	return 0;
}