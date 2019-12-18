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
union i2c_smbus_data {int* block; } ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  SIS630_BLOCK_DATA ; 
 scalar_t__ SMB_BYTE ; 
 scalar_t__ SMB_COUNT ; 
 scalar_t__ SMB_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 void* sis630_read (scalar_t__) ; 
 int /*<<< orphan*/  sis630_transaction_end (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int sis630_transaction_start (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sis630_transaction_wait (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis630_write (scalar_t__,int) ; 

__attribute__((used)) static int sis630_block_data(struct i2c_adapter *adap, union i2c_smbus_data *data, int read_write)
{
	int i, len = 0, rc = 0;
	u8 oldclock = 0;

	if (read_write == I2C_SMBUS_WRITE) {
		len = data->block[0];
		if (len < 0)
			len = 0;
		else if (len > 32)
			len = 32;
		sis630_write(SMB_COUNT, len);
		for (i=1; i <= len; i++) {
			dev_dbg(&adap->dev, "set data 0x%02x\n", data->block[i]);
			/* set data */
			sis630_write(SMB_BYTE+(i-1)%8, data->block[i]);
			if (i==8 || (len<8 && i==len)) {
				dev_dbg(&adap->dev, "start trans len=%d i=%d\n",len ,i);
				/* first transaction */
				rc = sis630_transaction_start(adap,
						SIS630_BLOCK_DATA, &oldclock);
				if (rc)
					return rc;
			}
			else if ((i-1)%8 == 7 || i==len) {
				dev_dbg(&adap->dev, "trans_wait len=%d i=%d\n",len,i);
				if (i>8) {
					dev_dbg(&adap->dev, "clear smbary_sts len=%d i=%d\n",len,i);
					/*
					   If this is not first transaction,
					   we must clear sticky bit.
					   clear SMBARY_STS
					*/
					sis630_write(SMB_STS,0x10);
				}
				rc = sis630_transaction_wait(adap,
						SIS630_BLOCK_DATA);
				if (rc) {
					dev_dbg(&adap->dev, "trans_wait failed\n");
					break;
				}
			}
		}
	}
	else {
		/* read request */
		data->block[0] = len = 0;
		rc = sis630_transaction_start(adap,
				SIS630_BLOCK_DATA, &oldclock);
		if (rc)
			return rc;
		do {
			rc = sis630_transaction_wait(adap, SIS630_BLOCK_DATA);
			if (rc) {
				dev_dbg(&adap->dev, "trans_wait failed\n");
				break;
			}
			/* if this first transaction then read byte count */
			if (len == 0)
				data->block[0] = sis630_read(SMB_COUNT);

			/* just to be sure */
			if (data->block[0] > 32)
				data->block[0] = 32;

			dev_dbg(&adap->dev, "block data read len=0x%x\n", data->block[0]);

			for (i=0; i < 8 && len < data->block[0]; i++,len++) {
				dev_dbg(&adap->dev, "read i=%d len=%d\n", i, len);
				data->block[len+1] = sis630_read(SMB_BYTE+i);
			}

			dev_dbg(&adap->dev, "clear smbary_sts len=%d i=%d\n",len,i);

			/* clear SMBARY_STS */
			sis630_write(SMB_STS,0x10);
		} while(len < data->block[0]);
	}

	sis630_transaction_end(adap, oldclock);

	return rc;
}