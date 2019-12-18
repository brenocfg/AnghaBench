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
struct rs5c372 {int /*<<< orphan*/  rtc; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rs5c372* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct rs5c372*) ; 
 int /*<<< orphan*/  rs5c_sysfs_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs5c372_remove(struct i2c_client *client)
{
	struct rs5c372 *rs5c372 = i2c_get_clientdata(client);

	rtc_device_unregister(rs5c372->rtc);
	rs5c_sysfs_unregister(&client->dev);
	kfree(rs5c372);
	return 0;
}