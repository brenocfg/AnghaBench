#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union i2c_smbus_data {int byte; int* block; int /*<<< orphan*/  word; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {struct bfin_twi_iface* algo_data; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct bfin_twi_iface {int writeNum; int readNum; int* transPtr; int cur_mode; scalar_t__ result; int manual_stop; char read_write; int command; int timeout_count; int /*<<< orphan*/  complete; TYPE_1__ timeout_timer; } ;

/* Variables and functions */
 int BUSBUSY ; 
 int CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ ; 
 int ENXIO ; 
 int FAST ; 
#define  I2C_SMBUS_BLOCK_DATA 136 
#define  I2C_SMBUS_BYTE 135 
#define  I2C_SMBUS_BYTE_DATA 134 
#define  I2C_SMBUS_I2C_BLOCK_DATA 133 
#define  I2C_SMBUS_PROC_CALL 132 
#define  I2C_SMBUS_QUICK 131 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 130 
 int MCOMP ; 
 int MDIR ; 
 int MEN ; 
 int MERR ; 
 scalar_t__ POLL_TIMEOUT ; 
 int RCVSERV ; 
 int /*<<< orphan*/  SSYNC () ; 
 int TWI_ENA ; 
#define  TWI_I2C_MODE_COMBINED 129 
 void* TWI_I2C_MODE_STANDARD ; 
#define  TWI_I2C_MODE_STANDARDSUB 128 
 int XMTSERV ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int read_CONTROL (struct bfin_twi_iface*) ; 
 int read_MASTER_CTL (struct bfin_twi_iface*) ; 
 int read_MASTER_STAT (struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_FIFO_CTL (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_INT_MASK (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_INT_STAT (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_MASTER_ADDR (struct bfin_twi_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_MASTER_CTL (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_XMT_DATA8 (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  yield () ; 

int bfin_twi_smbus_xfer(struct i2c_adapter *adap, u16 addr,
			unsigned short flags, char read_write,
			u8 command, int size, union i2c_smbus_data *data)
{
	struct bfin_twi_iface *iface = adap->algo_data;
	int rc = 0;

	if (!(read_CONTROL(iface) & TWI_ENA))
		return -ENXIO;

	while (read_MASTER_STAT(iface) & BUSBUSY)
		yield();

	iface->writeNum = 0;
	iface->readNum = 0;

	/* Prepare datas & select mode */
	switch (size) {
	case I2C_SMBUS_QUICK:
		iface->transPtr = NULL;
		iface->cur_mode = TWI_I2C_MODE_STANDARD;
		break;
	case I2C_SMBUS_BYTE:
		if (data == NULL)
			iface->transPtr = NULL;
		else {
			if (read_write == I2C_SMBUS_READ)
				iface->readNum = 1;
			else
				iface->writeNum = 1;
			iface->transPtr = &data->byte;
		}
		iface->cur_mode = TWI_I2C_MODE_STANDARD;
		break;
	case I2C_SMBUS_BYTE_DATA:
		if (read_write == I2C_SMBUS_READ) {
			iface->readNum = 1;
			iface->cur_mode = TWI_I2C_MODE_COMBINED;
		} else {
			iface->writeNum = 1;
			iface->cur_mode = TWI_I2C_MODE_STANDARDSUB;
		}
		iface->transPtr = &data->byte;
		break;
	case I2C_SMBUS_WORD_DATA:
		if (read_write == I2C_SMBUS_READ) {
			iface->readNum = 2;
			iface->cur_mode = TWI_I2C_MODE_COMBINED;
		} else {
			iface->writeNum = 2;
			iface->cur_mode = TWI_I2C_MODE_STANDARDSUB;
		}
		iface->transPtr = (u8 *)&data->word;
		break;
	case I2C_SMBUS_PROC_CALL:
		iface->writeNum = 2;
		iface->readNum = 2;
		iface->cur_mode = TWI_I2C_MODE_COMBINED;
		iface->transPtr = (u8 *)&data->word;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		if (read_write == I2C_SMBUS_READ) {
			iface->readNum = 0;
			iface->cur_mode = TWI_I2C_MODE_COMBINED;
		} else {
			iface->writeNum = data->block[0] + 1;
			iface->cur_mode = TWI_I2C_MODE_STANDARDSUB;
		}
		iface->transPtr = data->block;
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		if (read_write == I2C_SMBUS_READ) {
			iface->readNum = data->block[0];
			iface->cur_mode = TWI_I2C_MODE_COMBINED;
		} else {
			iface->writeNum = data->block[0];
			iface->cur_mode = TWI_I2C_MODE_STANDARDSUB;
		}
		iface->transPtr = (u8 *)&data->block[1];
		break;
	default:
		return -1;
	}

	iface->result = 0;
	iface->manual_stop = 0;
	iface->read_write = read_write;
	iface->command = command;
	iface->timeout_count = 10;
	init_completion(&(iface->complete));

	/* FIFO Initiation. Data in FIFO should be discarded before
	 * start a new operation.
	 */
	write_FIFO_CTL(iface, 0x3);
	SSYNC();
	write_FIFO_CTL(iface, 0);

	/* clear int stat */
	write_INT_STAT(iface, MERR | MCOMP | XMTSERV | RCVSERV);

	/* Set Transmit device address */
	write_MASTER_ADDR(iface, addr);
	SSYNC();

	iface->timeout_timer.expires = jiffies + POLL_TIMEOUT;
	add_timer(&iface->timeout_timer);

	switch (iface->cur_mode) {
	case TWI_I2C_MODE_STANDARDSUB:
		write_XMT_DATA8(iface, iface->command);
		write_INT_MASK(iface, MCOMP | MERR |
			((iface->read_write == I2C_SMBUS_READ) ?
			RCVSERV : XMTSERV));
		SSYNC();

		if (iface->writeNum + 1 <= 255)
			write_MASTER_CTL(iface, (iface->writeNum + 1) << 6);
		else {
			write_MASTER_CTL(iface, 0xff << 6);
			iface->manual_stop = 1;
		}
		/* Master enable */
		write_MASTER_CTL(iface, read_MASTER_CTL(iface) | MEN |
			((CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ>100) ? FAST : 0));
		break;
	case TWI_I2C_MODE_COMBINED:
		write_XMT_DATA8(iface, iface->command);
		write_INT_MASK(iface, MCOMP | MERR | RCVSERV | XMTSERV);
		SSYNC();

		if (iface->writeNum > 0)
			write_MASTER_CTL(iface, (iface->writeNum + 1) << 6);
		else
			write_MASTER_CTL(iface, 0x1 << 6);
		/* Master enable */
		write_MASTER_CTL(iface, read_MASTER_CTL(iface) | MEN |
			((CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ>100) ? FAST : 0));
		break;
	default:
		write_MASTER_CTL(iface, 0);
		if (size != I2C_SMBUS_QUICK) {
			/* Don't access xmit data register when this is a
			 * read operation.
			 */
			if (iface->read_write != I2C_SMBUS_READ) {
				if (iface->writeNum > 0) {
					write_XMT_DATA8(iface,
						*(iface->transPtr++));
					if (iface->writeNum <= 255)
						write_MASTER_CTL(iface,
							iface->writeNum << 6);
					else {
						write_MASTER_CTL(iface,
							0xff << 6);
						iface->manual_stop = 1;
					}
					iface->writeNum--;
				} else {
					write_XMT_DATA8(iface, iface->command);
					write_MASTER_CTL(iface, 1 << 6);
				}
			} else {
				if (iface->readNum > 0 && iface->readNum <= 255)
					write_MASTER_CTL(iface,
						iface->readNum << 6);
				else if (iface->readNum > 255) {
					write_MASTER_CTL(iface, 0xff << 6);
					iface->manual_stop = 1;
				} else {
					del_timer(&iface->timeout_timer);
					break;
				}
			}
		}
		write_INT_MASK(iface, MCOMP | MERR |
			((iface->read_write == I2C_SMBUS_READ) ?
			RCVSERV : XMTSERV));
		SSYNC();

		/* Master enable */
		write_MASTER_CTL(iface, read_MASTER_CTL(iface) | MEN |
			((iface->read_write == I2C_SMBUS_READ) ? MDIR : 0) |
			((CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ > 100) ? FAST : 0));
		break;
	}
	SSYNC();

	wait_for_completion(&iface->complete);

	rc = (iface->result >= 0) ? 0 : -1;

	return rc;
}