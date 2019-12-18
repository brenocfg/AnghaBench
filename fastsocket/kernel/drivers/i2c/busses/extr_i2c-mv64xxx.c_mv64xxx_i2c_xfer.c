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
struct mv64xxx_i2c_data {int dummy; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 struct mv64xxx_i2c_data* i2c_get_adapdata (struct i2c_adapter*) ; 
 int mv64xxx_i2c_execute_msg (struct mv64xxx_i2c_data*,struct i2c_msg*) ; 

__attribute__((used)) static int
mv64xxx_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct mv64xxx_i2c_data *drv_data = i2c_get_adapdata(adap);
	int	i, rc;

	for (i=0; i<num; i++)
		if ((rc = mv64xxx_i2c_execute_msg(drv_data, &msgs[i])) < 0)
			return rc;

	return num;
}