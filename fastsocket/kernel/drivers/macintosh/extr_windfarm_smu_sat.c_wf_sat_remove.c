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
struct wf_sat {int /*<<< orphan*/ * i2c; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct wf_sat* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_sat_remove(struct i2c_client *client)
{
	struct wf_sat *sat = i2c_get_clientdata(client);

	/* XXX TODO */

	sat->i2c = NULL;
	i2c_set_clientdata(client, NULL);
	return 0;
}