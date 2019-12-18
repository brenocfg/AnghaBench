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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  detach_fcu () ; 
 int /*<<< orphan*/  dispose_control_loops () ; 
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ state ; 
 scalar_t__ state_detached ; 
 scalar_t__ state_detaching ; 
 int /*<<< orphan*/  stop_control_loops () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * u3_0 ; 
 int /*<<< orphan*/ * u3_1 ; 

__attribute__((used)) static int therm_pm72_remove(struct i2c_client *client)
{
	struct i2c_adapter *adapter = client->adapter;

	mutex_lock(&driver_lock);

	if (state != state_detached)
		state = state_detaching;

	/* Stop control loops if any */
	DBG("stopping control loops\n");
	mutex_unlock(&driver_lock);
	stop_control_loops();
	mutex_lock(&driver_lock);

	if (u3_0 != NULL && !strcmp(adapter->name, "u3 0")) {
		DBG("lost U3-0, disposing control loops\n");
		dispose_control_loops();
		u3_0 = NULL;
	}
	
	if (u3_1 != NULL && !strcmp(adapter->name, "u3 1")) {
		DBG("lost U3-1, detaching FCU\n");
		detach_fcu();
		u3_1 = NULL;
	}
	if (u3_0 == NULL && u3_1 == NULL)
		state = state_detached;

	mutex_unlock(&driver_lock);

	return 0;
}