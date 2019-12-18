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
union i2c_smbus_data {int byte; int* block; int /*<<< orphan*/  word; } ;
typedef  int u8 ;
typedef  int u16 ;
struct scx200_acb_iface {int address_byte; int command; int* ptr; int len; int result; scalar_t__ state; int /*<<< orphan*/  mutex; scalar_t__ needs_reset; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACBCTL1 ; 
 int ACBCTL1_START ; 
 int EINVAL ; 
 int I2C_SMBUS_BLOCK_MAX ; 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct scx200_acb_iface* i2c_get_adapdata (struct i2c_adapter*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  scx200_acb_poll (struct scx200_acb_iface*) ; 
 int /*<<< orphan*/  scx200_acb_reset (struct scx200_acb_iface*) ; 
 scalar_t__ state_address ; 
 scalar_t__ state_idle ; 
 scalar_t__ state_quick ; 

__attribute__((used)) static s32 scx200_acb_smbus_xfer(struct i2c_adapter *adapter,
				 u16 address, unsigned short flags,
				 char rw, u8 command, int size,
				 union i2c_smbus_data *data)
{
	struct scx200_acb_iface *iface = i2c_get_adapdata(adapter);
	int len;
	u8 *buffer;
	u16 cur_word;
	int rc;

	switch (size) {
	case I2C_SMBUS_QUICK:
		len = 0;
		buffer = NULL;
		break;

	case I2C_SMBUS_BYTE:
		len = 1;
		buffer = rw ? &data->byte : &command;
		break;

	case I2C_SMBUS_BYTE_DATA:
		len = 1;
		buffer = &data->byte;
		break;

	case I2C_SMBUS_WORD_DATA:
		len = 2;
		cur_word = cpu_to_le16(data->word);
		buffer = (u8 *)&cur_word;
		break;

	case I2C_SMBUS_I2C_BLOCK_DATA:
		len = data->block[0];
		if (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
			return -EINVAL;
		buffer = &data->block[1];
		break;

	default:
		return -EINVAL;
	}

	dev_dbg(&adapter->dev,
		"size=%d, address=0x%x, command=0x%x, len=%d, read=%d\n",
		size, address, command, len, rw);

	if (!len && rw == I2C_SMBUS_READ) {
		dev_dbg(&adapter->dev, "zero length read\n");
		return -EINVAL;
	}

	mutex_lock(&iface->mutex);

	iface->address_byte = (address << 1) | rw;
	iface->command = command;
	iface->ptr = buffer;
	iface->len = len;
	iface->result = -EINVAL;
	iface->needs_reset = 0;

	outb(inb(ACBCTL1) | ACBCTL1_START, ACBCTL1);

	if (size == I2C_SMBUS_QUICK || size == I2C_SMBUS_BYTE)
		iface->state = state_quick;
	else
		iface->state = state_address;

	while (iface->state != state_idle)
		scx200_acb_poll(iface);

	if (iface->needs_reset)
		scx200_acb_reset(iface);

	rc = iface->result;

	mutex_unlock(&iface->mutex);

	if (rc == 0 && size == I2C_SMBUS_WORD_DATA && rw == I2C_SMBUS_READ)
		data->word = le16_to_cpu(cur_word);

#ifdef DEBUG
	dev_dbg(&adapter->dev, "transfer done, result: %d", rc);
	if (buffer) {
		int i;
		printk(" data:");
		for (i = 0; i < len; ++i)
			printk(" %02x", buffer[i]);
	}
	printk("\n");
#endif

	return rc;
}