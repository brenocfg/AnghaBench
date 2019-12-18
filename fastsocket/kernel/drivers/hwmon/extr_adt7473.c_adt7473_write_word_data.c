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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,scalar_t__,int) ; 

__attribute__((used)) static inline int adt7473_write_word_data(struct i2c_client *client, u8 reg,
					  u16 value)
{
	return i2c_smbus_write_byte_data(client, reg, value & 0xFF)
	       && i2c_smbus_write_byte_data(client, reg + 1, value >> 8);
}