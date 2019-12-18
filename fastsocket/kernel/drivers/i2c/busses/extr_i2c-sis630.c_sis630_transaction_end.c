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
 int /*<<< orphan*/  SMB_CNT ; 
 int /*<<< orphan*/  SMB_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ high_clock ; 
 int sis630_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis630_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sis630_transaction_end(struct i2c_adapter *adap, u8 oldclock)
{
	int temp = 0;

	/* clear all status "sticky" bits */
	sis630_write(SMB_STS, temp);

	dev_dbg(&adap->dev, "SMB_CNT before clock restore 0x%02x\n", sis630_read(SMB_CNT));

	/*
	 * restore old Host Master Clock if high_clock is set
	 * and oldclock was not 56KHz
	 */
	if (high_clock && !(oldclock & 0x20))
		sis630_write(SMB_CNT,(sis630_read(SMB_CNT) & ~0x20));

	dev_dbg(&adap->dev, "SMB_CNT after clock restore 0x%02x\n", sis630_read(SMB_CNT));
}