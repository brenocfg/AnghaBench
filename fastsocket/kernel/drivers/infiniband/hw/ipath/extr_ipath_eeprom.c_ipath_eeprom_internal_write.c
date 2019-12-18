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
struct ipath_devdata {int dummy; } ;
struct i2c_chain_desc {int eeprom_dev; } ;

/* Variables and functions */
 int IPATH_NO_DEV ; 
 int READ_CMD ; 
 int WRITE_CMD ; 
 scalar_t__ i2c_startcmd (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_dbg (char*,...) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 struct i2c_chain_desc* ipath_i2c_type (struct ipath_devdata*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rd_byte (struct ipath_devdata*) ; 
 int /*<<< orphan*/  stop_cmd (struct ipath_devdata*) ; 
 int wr_byte (struct ipath_devdata*,int) ; 

__attribute__((used)) static int ipath_eeprom_internal_write(struct ipath_devdata *dd, u8 eeprom_offset,
				       const void *buffer, int len)
{
	int sub_len;
	const u8 *bp = buffer;
	int max_wait_time, i;
	int ret;
	struct i2c_chain_desc *icd;

	ret = 1;
	icd = ipath_i2c_type(dd);
	if (!icd)
		goto bail;

	while (len > 0) {
		if (icd->eeprom_dev == IPATH_NO_DEV) {
			if (i2c_startcmd(dd,
					 (eeprom_offset << 1) | WRITE_CMD)) {
				ipath_dbg("Failed to start cmd offset %u\n",
					eeprom_offset);
				goto failed_write;
			}
		} else {
			/* Real I2C */
			if (i2c_startcmd(dd, icd->eeprom_dev | WRITE_CMD)) {
				ipath_dbg("Failed EEPROM startcmd\n");
				goto failed_write;
			}
			ret = wr_byte(dd, eeprom_offset);
			if (ret) {
				ipath_dev_err(dd, "Failed to write EEPROM "
					      "address\n");
				goto failed_write;
			}
		}

		sub_len = min(len, 4);
		eeprom_offset += sub_len;
		len -= sub_len;

		for (i = 0; i < sub_len; i++) {
			if (wr_byte(dd, *bp++)) {
				ipath_dbg("no ack after byte %u/%u (%u "
					  "total remain)\n", i, sub_len,
					  len + sub_len - i);
				goto failed_write;
			}
		}

		stop_cmd(dd);

		/*
		 * wait for write complete by waiting for a successful
		 * read (the chip replies with a zero after the write
		 * cmd completes, and before it writes to the eeprom.
		 * The startcmd for the read will fail the ack until
		 * the writes have completed.   We do this inline to avoid
		 * the debug prints that are in the real read routine
		 * if the startcmd fails.
		 * We also use the proper device address, so it doesn't matter
		 * whether we have real eeprom_dev. legacy likes any address.
		 */
		max_wait_time = 100;
		while (i2c_startcmd(dd, icd->eeprom_dev | READ_CMD)) {
			stop_cmd(dd);
			if (!--max_wait_time) {
				ipath_dbg("Did not get successful read to "
					  "complete write\n");
				goto failed_write;
			}
		}
		/* now read (and ignore) the resulting byte */
		rd_byte(dd);
		stop_cmd(dd);
	}

	ret = 0;
	goto bail;

failed_write:
	stop_cmd(dd);
	ret = 1;

bail:
	return ret;
}