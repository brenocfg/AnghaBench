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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MAX_TIMEOUT ; 
 int SIS630_BLOCK_DATA ; 
 int /*<<< orphan*/  SMB_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sis630_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sis630_transaction_wait(struct i2c_adapter *adap, int size)
{
	int temp, result = 0, timeout = 0;

	/* We will always wait for a fraction of a second! */
	do {
		msleep(1);
		temp = sis630_read(SMB_STS);
		/* check if block transmitted */
		if (size == SIS630_BLOCK_DATA && (temp & 0x10))
			break;
	} while (!(temp & 0x0e) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	}

	if (temp & 0x02) {
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
		result = -ENXIO;
	}

	if (temp & 0x04) {
		dev_err(&adap->dev, "Bus collision!\n");
		result = -EIO;
		/*
		  TBD: Datasheet say:
		  the software should clear this bit and restart SMBUS operation.
		  Should we do it or user start request again?
		*/
	}

	return result;
}