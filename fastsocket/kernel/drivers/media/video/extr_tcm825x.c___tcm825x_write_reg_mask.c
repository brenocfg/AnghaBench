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
typedef  int u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int tcm825x_read_reg (struct i2c_client*,int) ; 
 int tcm825x_write_reg (struct i2c_client*,int,int) ; 

__attribute__((used)) static int __tcm825x_write_reg_mask(struct i2c_client *client,
				    u8 reg, u8 val, u8 mask)
{
	int rc;

	/* need to do read - modify - write */
	rc = tcm825x_read_reg(client, reg);
	if (rc < 0)
		return rc;

	rc &= (~mask);	/* Clear the masked bits */
	val &= mask;	/* Enforce mask on value */
	val |= rc;

	/* write the new value to the register */
	rc = tcm825x_write_reg(client, reg, val);
	if (rc)
		return rc;

	return 0;
}