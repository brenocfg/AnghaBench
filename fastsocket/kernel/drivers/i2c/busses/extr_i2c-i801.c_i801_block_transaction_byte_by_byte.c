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
union i2c_smbus_data {int* block; } ;
struct i801_priv {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENABLE_INT9 ; 
 int EPROTO ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int I2C_SMBUS_I2C_BLOCK_DATA ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int I801_BLOCK_DATA ; 
 int I801_BLOCK_LAST ; 
 int I801_I2C_BLOCK_DATA ; 
 int I801_I2C_BLOCK_LAST ; 
 int I801_START ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMBBLKDAT (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTDAT0 (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_BYTE_DONE ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int SMBHSTSTS_INTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i801_check_post (struct i801_priv*,int,int) ; 
 int i801_check_pre (struct i801_priv*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i801_block_transaction_byte_by_byte(struct i801_priv *priv,
					       union i2c_smbus_data *data,
					       char read_write, int command,
					       int hwpec)
{
	int i, len;
	int smbcmd;
	int status;
	int result;
	int timeout;

	result = i801_check_pre(priv);
	if (result < 0)
		return result;

	len = data->block[0];

	if (read_write == I2C_SMBUS_WRITE) {
		outb_p(len, SMBHSTDAT0(priv));
		outb_p(data->block[1], SMBBLKDAT(priv));
	}

	for (i = 1; i <= len; i++) {
		if (i == len && read_write == I2C_SMBUS_READ) {
			if (command == I2C_SMBUS_I2C_BLOCK_DATA)
				smbcmd = I801_I2C_BLOCK_LAST;
			else
				smbcmd = I801_BLOCK_LAST;
		} else {
			if (command == I2C_SMBUS_I2C_BLOCK_DATA
			 && read_write == I2C_SMBUS_READ)
				smbcmd = I801_I2C_BLOCK_DATA;
			else
				smbcmd = I801_BLOCK_DATA;
		}
		outb_p(smbcmd | ENABLE_INT9, SMBHSTCNT(priv));

		if (i == 1)
			outb_p(inb(SMBHSTCNT(priv)) | I801_START,
			       SMBHSTCNT(priv));

		/* We will always wait for a fraction of a second! */
		timeout = 0;
		do {
			msleep(1);
			status = inb_p(SMBHSTSTS(priv));
		} while ((!(status & SMBHSTSTS_BYTE_DONE))
			 && (timeout++ < MAX_TIMEOUT));

		result = i801_check_post(priv, status, timeout > MAX_TIMEOUT);
		if (result < 0)
			return result;

		if (i == 1 && read_write == I2C_SMBUS_READ
		 && command != I2C_SMBUS_I2C_BLOCK_DATA) {
			len = inb_p(SMBHSTDAT0(priv));
			if (len < 1 || len > I2C_SMBUS_BLOCK_MAX) {
				dev_err(&priv->pci_dev->dev,
					"Illegal SMBus block read size %d\n",
					len);
				/* Recover */
				while (inb_p(SMBHSTSTS(priv)) &
				       SMBHSTSTS_HOST_BUSY)
					outb_p(SMBHSTSTS_BYTE_DONE,
					       SMBHSTSTS(priv));
				outb_p(SMBHSTSTS_INTR, SMBHSTSTS(priv));
				return -EPROTO;
			}
			data->block[0] = len;
		}

		/* Retrieve/store value in SMBBLKDAT */
		if (read_write == I2C_SMBUS_READ)
			data->block[i] = inb_p(SMBBLKDAT(priv));
		if (read_write == I2C_SMBUS_WRITE && i+1 <= len)
			outb_p(data->block[i+1], SMBBLKDAT(priv));

		/* signals SMBBLKDAT ready */
		outb_p(SMBHSTSTS_BYTE_DONE | SMBHSTSTS_INTR, SMBHSTSTS(priv));
	}

	return 0;
}