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
struct i2c_algo_bit_data {int dummy; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; struct i2c_algo_bit_data* algo_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ bit_test ; 
 int /*<<< orphan*/  i2c_bit_algo ; 
 int test_bus (struct i2c_algo_bit_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_bit_prepare_bus(struct i2c_adapter *adap)
{
	struct i2c_algo_bit_data *bit_adap = adap->algo_data;

	if (bit_test) {
		int ret = test_bus(bit_adap, adap->name);
		if (ret < 0)
			return -ENODEV;
	}

	/* register new adapter to i2c module... */
	adap->algo = &i2c_bit_algo;
	adap->retries = 3;

	return 0;
}