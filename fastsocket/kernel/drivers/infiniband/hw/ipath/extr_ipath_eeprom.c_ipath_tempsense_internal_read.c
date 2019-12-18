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
struct ipath_devdata {int dummy; } ;
struct i2c_chain_desc {int temp_dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int IPATH_NO_DEV ; 
 int READ_CMD ; 
 int WRITE_CMD ; 
 scalar_t__ i2c_startcmd (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_dbg (char*) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,int /*<<< orphan*/ ) ; 
 struct i2c_chain_desc* ipath_i2c_type (struct ipath_devdata*) ; 
 int rd_byte (struct ipath_devdata*) ; 
 int /*<<< orphan*/  stop_cmd (struct ipath_devdata*) ; 
 int wr_byte (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipath_tempsense_internal_read(struct ipath_devdata *dd, u8 regnum)
{
	int ret;
	struct i2c_chain_desc *icd;

	ret = -ENOENT;

	icd = ipath_i2c_type(dd);
	if (!icd)
		goto bail;

	if (icd->temp_dev == IPATH_NO_DEV) {
		/* tempsense only exists on new, real-I2C boards */
		ret = -ENXIO;
		goto bail;
	}

	if (i2c_startcmd(dd, icd->temp_dev | WRITE_CMD)) {
		ipath_dbg("Failed tempsense startcmd\n");
		stop_cmd(dd);
		ret = -ENXIO;
		goto bail;
	}
	ret = wr_byte(dd, regnum);
	stop_cmd(dd);
	if (ret) {
		ipath_dev_err(dd, "Failed tempsense WR command %02X\n",
			      regnum);
		ret = -ENXIO;
		goto bail;
	}
	if (i2c_startcmd(dd, icd->temp_dev | READ_CMD)) {
		ipath_dbg("Failed tempsense RD startcmd\n");
		stop_cmd(dd);
		ret = -ENXIO;
		goto bail;
	}
	/*
	 * We can only clock out one byte per command, sensibly
	 */
	ret = rd_byte(dd);
	stop_cmd(dd);

bail:
	return ret;
}