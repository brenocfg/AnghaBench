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
struct dvb_usb_adapter {int /*<<< orphan*/  fe; struct dibusb_state* priv; } ;
struct TYPE_2__ {scalar_t__ (* pid_parse ) (int /*<<< orphan*/ ,int) ;} ;
struct dibusb_state {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

int dibusb_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	if (adap->priv != NULL) {
		struct dibusb_state *st = adap->priv;
		if (st->ops.pid_parse != NULL)
			if (st->ops.pid_parse(adap->fe,onoff) < 0)
				err("could not handle pid_parser");
	}
	return 0;
}