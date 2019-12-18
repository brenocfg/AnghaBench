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
struct fschmd_data {int watchdog_control; size_t kind; int /*<<< orphan*/  watchdog_lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * FSCHMD_REG_WDOG_CONTROL ; 
 int FSCHMD_WDOG_CONTROL_STARTED ; 
 int FSCHMD_WDOG_CONTROL_STOP ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchdog_stop(struct fschmd_data *data)
{
	int ret = 0;

	mutex_lock(&data->watchdog_lock);
	if (!data->client) {
		ret = -ENODEV;
		goto leave;
	}

	data->watchdog_control &= ~FSCHMD_WDOG_CONTROL_STARTED;
	/* Don't store the stop flag in our watchdog control register copy, as
	   its a write only bit (read always returns 0) */
	i2c_smbus_write_byte_data(data->client,
		FSCHMD_REG_WDOG_CONTROL[data->kind],
		data->watchdog_control | FSCHMD_WDOG_CONTROL_STOP);
leave:
	mutex_unlock(&data->watchdog_lock);
	return ret;
}