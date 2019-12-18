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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct wf_lm75_sensor {TYPE_1__ sens; int /*<<< orphan*/ * i2c; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct wf_lm75_sensor* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_unregister_sensor (TYPE_1__*) ; 

__attribute__((used)) static int wf_lm75_remove(struct i2c_client *client)
{
	struct wf_lm75_sensor *lm = i2c_get_clientdata(client);

	DBG("wf_lm75: i2c detatch called for %s\n", lm->sens.name);

	/* Mark client detached */
	lm->i2c = NULL;

	/* release sensor */
	wf_unregister_sensor(&lm->sens);

	i2c_set_clientdata(client, NULL);
	return 0;
}