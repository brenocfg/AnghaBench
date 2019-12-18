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
struct i2c_algo_dp_aux_data {int running; } ;
struct i2c_adapter {struct i2c_algo_dp_aux_data* algo_data; } ;

/* Variables and functions */
 int MODE_I2C_READ ; 
 int MODE_I2C_STOP ; 
 int MODE_I2C_WRITE ; 
 int /*<<< orphan*/  i2c_algo_dp_aux_transaction (struct i2c_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
i2c_algo_dp_aux_stop(struct i2c_adapter *adapter, bool reading)
{
	struct i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	int mode = MODE_I2C_STOP;

	if (reading)
		mode |= MODE_I2C_READ;
	else
		mode |= MODE_I2C_WRITE;
	if (algo_data->running) {
		(void) i2c_algo_dp_aux_transaction(adapter, mode, 0, NULL);
		algo_data->running = false;
	}
}