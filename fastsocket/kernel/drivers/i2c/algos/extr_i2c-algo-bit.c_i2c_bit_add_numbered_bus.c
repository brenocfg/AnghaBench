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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int i2c_bit_prepare_bus (struct i2c_adapter*) ; 

int i2c_bit_add_numbered_bus(struct i2c_adapter *adap)
{
	int err;

	err = i2c_bit_prepare_bus(adap);
	if (err)
		return err;

	return i2c_add_numbered_adapter(adap);
}