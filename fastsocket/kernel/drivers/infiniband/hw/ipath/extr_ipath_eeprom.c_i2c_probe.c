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
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int READ_CMD ; 
 int /*<<< orphan*/  VERBOSE ; 
 int eeprom_reset (struct ipath_devdata*) ; 
 int i2c_startcmd (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,int) ; 
 int rd_byte (struct ipath_devdata*) ; 
 int /*<<< orphan*/  stop_cmd (struct ipath_devdata*) ; 

__attribute__((used)) static int i2c_probe(struct ipath_devdata *dd, int devaddr)
{
	int ret = 0;

	ret = eeprom_reset(dd);
	if (ret) {
		ipath_dev_err(dd, "Failed reset probing device 0x%02X\n",
			      devaddr);
		return ret;
	}
	/*
	 * Reset no longer leaves bus in start condition, so normal
	 * i2c_startcmd() will do.
	 */
	ret = i2c_startcmd(dd, devaddr | READ_CMD);
	if (ret)
		ipath_cdbg(VERBOSE, "Failed startcmd for device 0x%02X\n",
			   devaddr);
	else {
		/*
		 * Device did respond. Complete a single-byte read, because some
		 * devices apparently cannot handle STOP immediately after they
		 * ACK the start-cmd.
		 */
		int data;
		data = rd_byte(dd);
		stop_cmd(dd);
		ipath_cdbg(VERBOSE, "Response from device 0x%02X\n", devaddr);
	}
	return ret;
}