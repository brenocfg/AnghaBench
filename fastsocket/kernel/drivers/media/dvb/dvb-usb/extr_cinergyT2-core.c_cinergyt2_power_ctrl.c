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
struct dvb_usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CINERGYT2_EP1_SLEEP_MODE ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,char*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cinergyt2_power_ctrl(struct dvb_usb_device *d, int enable)
{
	char buf[] = { CINERGYT2_EP1_SLEEP_MODE, enable ? 0 : 1 };
	char state[3];
	return dvb_usb_generic_rw(d, buf, sizeof(buf), state, sizeof(state), 0);
}