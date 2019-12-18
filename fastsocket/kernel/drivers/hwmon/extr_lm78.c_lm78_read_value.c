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
typedef  int /*<<< orphan*/  u8 ;
struct lm78_data {int /*<<< orphan*/  lock; scalar_t__ isa_addr; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ LM78_ADDR_REG_OFFSET ; 
 scalar_t__ LM78_DATA_REG_OFFSET ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lm78_read_value(struct lm78_data *data, u8 reg)
{
	struct i2c_client *client = data->client;

#ifdef CONFIG_ISA
	if (!client) { /* ISA device */
		int res;
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		res = inb_p(data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		return res;
	} else
#endif
		return i2c_smbus_read_byte_data(client, reg);
}