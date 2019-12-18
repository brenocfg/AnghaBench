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
typedef  scalar_t__ u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ AD7414_REG_TEMP ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,scalar_t__) ; 
 int swab16 (int) ; 

__attribute__((used)) static inline int ad7414_read(struct i2c_client *client, u8 reg)
{
	if (reg == AD7414_REG_TEMP) {
		int value = i2c_smbus_read_word_data(client, reg);
		return (value < 0) ? value : swab16(value);
	} else
		return i2c_smbus_read_byte_data(client, reg);
}