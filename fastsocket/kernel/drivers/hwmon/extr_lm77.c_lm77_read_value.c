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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ LM77_REG_CONF ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  i2c_smbus_read_word_data (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 lm77_read_value(struct i2c_client *client, u8 reg)
{
	if (reg == LM77_REG_CONF)
		return i2c_smbus_read_byte_data(client, reg);
	else
		return swab16(i2c_smbus_read_word_data(client, reg));
}