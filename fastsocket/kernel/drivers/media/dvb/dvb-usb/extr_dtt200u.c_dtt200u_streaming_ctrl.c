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
struct dvb_usb_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RESET_PID_FILTER ; 
 int SET_STREAMING ; 
 int /*<<< orphan*/  dvb_usb_generic_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int dtt200u_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	u8 b_streaming[2] = { SET_STREAMING, onoff };
	u8 b_rst_pid = RESET_PID_FILTER;

	dvb_usb_generic_write(adap->dev, b_streaming, 2);

	if (onoff == 0)
		dvb_usb_generic_write(adap->dev, &b_rst_pid, 1);
	return 0;
}