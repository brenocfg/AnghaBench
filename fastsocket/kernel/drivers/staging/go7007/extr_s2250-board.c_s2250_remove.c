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
struct s2250 {int /*<<< orphan*/  audio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct s2250* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s2250*) ; 

__attribute__((used)) static int s2250_remove(struct i2c_client *client)
{
	struct s2250 *dec = i2c_get_clientdata(client);

	i2c_set_clientdata(client, NULL);
	i2c_unregister_device(dec->audio);
	kfree(dec);
	return 0;
}