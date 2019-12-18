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
struct fschmd_data {int watchdog_control; int watchdog_preset; int /*<<< orphan*/  watchdog_lock; } ;

/* Variables and functions */
 int FSCHMD_WDOG_CONTROL_RESOLUTION ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchdog_get_timeout(struct fschmd_data *data)
{
	int timeout;

	mutex_lock(&data->watchdog_lock);
	if (data->watchdog_control & FSCHMD_WDOG_CONTROL_RESOLUTION)
		timeout = data->watchdog_preset * 60;
	else
		timeout = data->watchdog_preset * 2;
	mutex_unlock(&data->watchdog_lock);

	return timeout;
}