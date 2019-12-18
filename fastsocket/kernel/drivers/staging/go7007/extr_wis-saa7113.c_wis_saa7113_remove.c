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
struct wis_saa7113 {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct wis_saa7113* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wis_saa7113*) ; 

__attribute__((used)) static int wis_saa7113_remove(struct i2c_client *client)
{
	struct wis_saa7113 *dec = i2c_get_clientdata(client);

	i2c_set_clientdata(client, NULL);
	kfree(dec);
	return 0;
}