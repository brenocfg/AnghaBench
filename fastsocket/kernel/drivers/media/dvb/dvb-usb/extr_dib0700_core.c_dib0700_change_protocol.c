#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct rc_dev {struct dvb_usb_device* priv; } ;
struct TYPE_3__ {scalar_t__ protocol; } ;
struct TYPE_4__ {TYPE_1__ rc_core; } ;
struct dvb_usb_device {TYPE_2__ props; struct dib0700_state* priv; } ;
struct dib0700_state {int fw_version; } ;
typedef  int /*<<< orphan*/  rc_setup ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RC_TYPE_NEC ; 
 scalar_t__ RC_TYPE_RC5 ; 
 scalar_t__ RC_TYPE_RC6 ; 
 int REQUEST_SET_RC ; 
 int dib0700_ctrl_wr (struct dvb_usb_device*,int*,int) ; 
 int /*<<< orphan*/  err (char*) ; 

int dib0700_change_protocol(struct rc_dev *rc, u64 rc_type)
{
	struct dvb_usb_device *d = rc->priv;
	struct dib0700_state *st = d->priv;
	u8 rc_setup[3] = { REQUEST_SET_RC, 0, 0 };
	int new_proto, ret;

	/* Set the IR mode */
	if (rc_type == RC_TYPE_RC5)
		new_proto = 1;
	else if (rc_type == RC_TYPE_NEC)
		new_proto = 0;
	else if (rc_type == RC_TYPE_RC6) {
		if (st->fw_version < 0x10200)
			return -EINVAL;

		new_proto = 2;
	} else
		return -EINVAL;

	rc_setup[1] = new_proto;

	ret = dib0700_ctrl_wr(d, rc_setup, sizeof(rc_setup));
	if (ret < 0) {
		err("ir protocol setup failed");
		return ret;
	}

	d->props.rc_core.protocol = rc_type;

	return ret;
}