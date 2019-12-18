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
typedef  int u16 ;
struct dvb_usb_adapter {int feedcount; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XD_MP2IF_PID_DATA_H ; 
 int /*<<< orphan*/  XD_MP2IF_PID_DATA_L ; 
 int /*<<< orphan*/  XD_MP2IF_PID_IDX ; 
 int af9005_pid_filter_control (struct dvb_usb_adapter*,int) ; 
 int af9005_write_ofdm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 

__attribute__((used)) static int af9005_pid_filter(struct dvb_usb_adapter *adap, int index,
			     u16 pid, int onoff)
{
	u8 cmd = index & 0x1f;
	int ret;
	deb_info("set pid filter, index %d, pid %x, onoff %d\n", index,
		 pid, onoff);
	if (onoff) {
		/* cannot use it as pid_filter_ctrl since it has to be done
		   before setting the first pid */
		if (adap->feedcount == 1) {
			deb_info("first pid set, enable pid table\n");
			ret = af9005_pid_filter_control(adap, onoff);
			if (ret)
				return ret;
		}
		ret =
		    af9005_write_ofdm_register(adap->dev,
					       XD_MP2IF_PID_DATA_L,
					       (u8) (pid & 0xff));
		if (ret)
			return ret;
		ret =
		    af9005_write_ofdm_register(adap->dev,
					       XD_MP2IF_PID_DATA_H,
					       (u8) (pid >> 8));
		if (ret)
			return ret;
		cmd |= 0x20 | 0x40;
	} else {
		if (adap->feedcount == 0) {
			deb_info("last pid unset, disable pid table\n");
			ret = af9005_pid_filter_control(adap, onoff);
			if (ret)
				return ret;
		}
	}
	ret = af9005_write_ofdm_register(adap->dev, XD_MP2IF_PID_IDX, cmd);
	if (ret)
		return ret;
	deb_info("set pid ok\n");
	return 0;
}