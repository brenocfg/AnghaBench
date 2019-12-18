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

/* Variables and functions */
 int IXGBE_I2C_DATA_IN ; 

__attribute__((used)) static bool ixgbe_get_i2c_data(u32 *i2cctl)
{
	bool data;

	if (*i2cctl & IXGBE_I2C_DATA_IN)
		data = true;
	else
		data = false;

	return data;
}