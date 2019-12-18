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
typedef  int u32 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int FEATURE_I2CBLOCK ; 
 int I2C_FUNC_SMBUS_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_QUICK ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int I2C_SMBUS_PROC_CALL ; 
 int vt596_features ; 

__attribute__((used)) static u32 vt596_func(struct i2c_adapter *adapter)
{
	u32 func = I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_SMBUS_PROC_CALL | I2C_FUNC_SMBUS_BLOCK_DATA;

	if (vt596_features & FEATURE_I2CBLOCK)
		func |= I2C_FUNC_SMBUS_I2C_BLOCK;
	return func;
}