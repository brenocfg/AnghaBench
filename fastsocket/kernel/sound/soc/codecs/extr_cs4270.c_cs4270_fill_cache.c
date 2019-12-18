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
struct snd_soc_codec {int /*<<< orphan*/  dev; struct i2c_client* control_data; int /*<<< orphan*/ * reg_cache; } ;
struct i2c_client {int /*<<< orphan*/  addr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CS4270_FIRSTREG ; 
 int CS4270_I2C_INCR ; 
 scalar_t__ CS4270_NUMREGS ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_smbus_read_i2c_block_data (struct i2c_client*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs4270_fill_cache(struct snd_soc_codec *codec)
{
	u8 *cache = codec->reg_cache;
	struct i2c_client *i2c_client = codec->control_data;
	s32 length;

	length = i2c_smbus_read_i2c_block_data(i2c_client,
		CS4270_FIRSTREG | CS4270_I2C_INCR, CS4270_NUMREGS, cache);

	if (length != CS4270_NUMREGS) {
		dev_err(codec->dev, "i2c read failure, addr=0x%x\n",
		       i2c_client->addr);
		return -EIO;
	}

	return 0;
}