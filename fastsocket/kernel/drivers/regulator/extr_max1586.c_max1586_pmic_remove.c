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
struct regulator_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int MAX1586_V6 ; 
 struct regulator_dev** i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct regulator_dev**) ; 
 int /*<<< orphan*/  regulator_unregister (struct regulator_dev*) ; 

__attribute__((used)) static int max1586_pmic_remove(struct i2c_client *client)
{
	struct regulator_dev **rdev = i2c_get_clientdata(client);
	int i;

	for (i = 0; i <= MAX1586_V6; i++)
		if (rdev[i])
			regulator_unregister(rdev[i]);
	kfree(rdev);
	i2c_set_clientdata(client, NULL);

	return 0;
}