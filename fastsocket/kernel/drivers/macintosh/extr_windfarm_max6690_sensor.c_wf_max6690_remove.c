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
struct wf_6690_sensor {int /*<<< orphan*/  sens; int /*<<< orphan*/ * i2c; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct wf_6690_sensor* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  wf_unregister_sensor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_max6690_remove(struct i2c_client *client)
{
	struct wf_6690_sensor *max = i2c_get_clientdata(client);

	max->i2c = NULL;
	wf_unregister_sensor(&max->sens);

	return 0;
}