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
struct i2c_adapter {int retries; int /*<<< orphan*/ * algo; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_dp_aux_algo ; 
 int /*<<< orphan*/  i2c_dp_aux_reset_bus (struct i2c_adapter*) ; 

__attribute__((used)) static int
i2c_dp_aux_prepare_bus(struct i2c_adapter *adapter)
{
	adapter->algo = &i2c_dp_aux_algo;
	adapter->retries = 3;
	i2c_dp_aux_reset_bus(adapter);
	return 0;
}