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
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ attach_fcu () ; 
 scalar_t__ create_control_loops () ; 
 int /*<<< orphan*/  driver_lock ; 
 struct i2c_adapter* k2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rackmac ; 
 int /*<<< orphan*/  start_control_loops () ; 
 scalar_t__ state ; 
 scalar_t__ state_attached ; 
 scalar_t__ state_attaching ; 
 scalar_t__ state_detached ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct i2c_adapter* u3_0 ; 
 struct i2c_adapter* u3_1 ; 

__attribute__((used)) static int therm_pm72_attach(struct i2c_adapter *adapter)
{
	mutex_lock(&driver_lock);

	/* Check state */
	if (state == state_detached)
		state = state_attaching;
	if (state != state_attaching) {
		mutex_unlock(&driver_lock);
		return 0;
	}

	/* Check if we are looking for one of these */
	if (u3_0 == NULL && !strcmp(adapter->name, "u3 0")) {
		u3_0 = adapter;
		DBG("found U3-0\n");
		if (k2 || !rackmac)
			if (create_control_loops())
				u3_0 = NULL;
	} else if (u3_1 == NULL && !strcmp(adapter->name, "u3 1")) {
		u3_1 = adapter;
		DBG("found U3-1, attaching FCU\n");
		if (attach_fcu())
			u3_1 = NULL;
	} else if (k2 == NULL && !strcmp(adapter->name, "mac-io 0")) {
		k2 = adapter;
		DBG("Found K2\n");
		if (u3_0 && rackmac)
			if (create_control_loops())
				k2 = NULL;
	}
	/* We got all we need, start control loops */
	if (u3_0 != NULL && u3_1 != NULL && (k2 || !rackmac)) {
		DBG("everything up, starting control loops\n");
		state = state_attached;
		start_control_loops();
	}
	mutex_unlock(&driver_lock);

	return 0;
}