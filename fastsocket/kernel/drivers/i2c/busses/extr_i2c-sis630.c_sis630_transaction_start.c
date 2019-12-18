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
typedef  int u8 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SMBHOST_CNT ; 
 int /*<<< orphan*/  SMB_CNT ; 
 int /*<<< orphan*/  SMB_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ high_clock ; 
 int sis630_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis630_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sis630_transaction_start(struct i2c_adapter *adap, int size, u8 *oldclock)
{
        int temp;

	/* Make sure the SMBus host is ready to start transmitting. */
	if ((temp = sis630_read(SMB_CNT) & 0x03) != 0x00) {
		dev_dbg(&adap->dev, "SMBus busy (%02x).Resetting...\n",temp);
		/* kill smbus transaction */
		sis630_write(SMBHOST_CNT, 0x20);

		if ((temp = sis630_read(SMB_CNT) & 0x03) != 0x00) {
			dev_dbg(&adap->dev, "Failed! (%02x)\n", temp);
			return -EBUSY;
                } else {
			dev_dbg(&adap->dev, "Successful!\n");
		}
        }

	/* save old clock, so we can prevent machine for hung */
	*oldclock = sis630_read(SMB_CNT);

	dev_dbg(&adap->dev, "saved clock 0x%02x\n", *oldclock);

	/* disable timeout interrupt , set Host Master Clock to 56KHz if requested */
	if (high_clock)
		sis630_write(SMB_CNT, 0x20);
	else
		sis630_write(SMB_CNT, (*oldclock & ~0x40));

	/* clear all sticky bits */
	temp = sis630_read(SMB_STS);
	sis630_write(SMB_STS, temp & 0x1e);

	/* start the transaction by setting bit 4 and size */
	sis630_write(SMBHOST_CNT,0x10 | (size & 0x07));

	return 0;
}