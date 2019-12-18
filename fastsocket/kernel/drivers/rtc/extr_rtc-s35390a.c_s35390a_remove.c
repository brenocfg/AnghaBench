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
struct s35390a {int /*<<< orphan*/  rtc; scalar_t__* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct s35390a* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct s35390a*) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s35390a_remove(struct i2c_client *client)
{
	unsigned int i;

	struct s35390a *s35390a = i2c_get_clientdata(client);
	for (i = 1; i < 8; ++i)
		if (s35390a->client[i])
			i2c_unregister_device(s35390a->client[i]);

	rtc_device_unregister(s35390a->rtc);
	kfree(s35390a);
	i2c_set_clientdata(client, NULL);

	return 0;
}