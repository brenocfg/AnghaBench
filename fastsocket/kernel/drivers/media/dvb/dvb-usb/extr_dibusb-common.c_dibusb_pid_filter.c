#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_adapter {int /*<<< orphan*/  fe; struct dibusb_state* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pid_ctrl ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct dibusb_state {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int dibusb_pid_filter(struct dvb_usb_adapter *adap, int index, u16 pid, int onoff)
{
	if (adap->priv != NULL) {
		struct dibusb_state *st = adap->priv;
		if (st->ops.pid_ctrl != NULL)
			st->ops.pid_ctrl(adap->fe,index,pid,onoff);
	}
	return 0;
}