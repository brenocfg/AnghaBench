#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tsl2561_state {int /*<<< orphan*/  command_buf_lock; TYPE_1__* command_buf; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int /*<<< orphan*/  address; scalar_t__ block; scalar_t__ word; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSL2561_CONTROL_REGISTER ; 
 int /*<<< orphan*/  TSL2561_CONT_REG_PWR_ON ; 
 int /*<<< orphan*/  TSL2561_INT_CONTROL_REGISTER ; 
 int /*<<< orphan*/  TSL2561_INT_REG_INT_TEST ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsl2561_initialize(struct tsl2561_state *st)
{
	int err;

	mutex_lock(&st->command_buf_lock);
	st->command_buf->word = 0;
	st->command_buf->block = 0;
	st->command_buf->address = TSL2561_CONTROL_REGISTER;
	err = i2c_smbus_write_byte_data(st->client, *(char *)(st->command_buf),
					TSL2561_CONT_REG_PWR_ON);
	if (err)
		goto error_ret;

	st->command_buf->address = TSL2561_INT_CONTROL_REGISTER;
	err = i2c_smbus_write_byte_data(st->client, *(char *)(st->command_buf),
					TSL2561_INT_REG_INT_TEST);

error_ret:
	mutex_unlock(&st->command_buf_lock);

	return err;
}