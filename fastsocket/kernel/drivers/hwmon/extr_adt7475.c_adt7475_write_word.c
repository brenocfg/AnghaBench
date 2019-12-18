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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static void adt7475_write_word(struct i2c_client *client, int reg, u16 val)
{
	i2c_smbus_write_byte_data(client, reg + 1, val >> 8);
	i2c_smbus_write_byte_data(client, reg, val & 0xFF);
}