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
typedef  int /*<<< orphan*/  u32 ;
struct st5481_in {int mode; int /*<<< orphan*/  counter; int /*<<< orphan*/  adapter; int /*<<< orphan*/  packet_size; int /*<<< orphan*/  ep; int /*<<< orphan*/  hdlc_state; int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLC_56KBIT ; 
 int /*<<< orphan*/  HDLC_BITREVERSE ; 
 scalar_t__ L1_MODE_HDLC_56K ; 
 int L1_MODE_NULL ; 
 scalar_t__ L1_MODE_TRANS ; 
 int /*<<< orphan*/  isdnhdlc_rcv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st5481_start_rcv (struct st5481_in*) ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5481_usb_pipe_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

void st5481_in_mode(struct st5481_in *in, int mode)
{
	if (in->mode == mode)
		return;

	in->mode = mode;

	usb_unlink_urb(in->urb[0]);
	usb_unlink_urb(in->urb[1]);

	if (in->mode != L1_MODE_NULL) {
		if (in->mode != L1_MODE_TRANS) {
			u32 features = HDLC_BITREVERSE;

			if (in->mode == L1_MODE_HDLC_56K)
				features |= HDLC_56KBIT;
			isdnhdlc_rcv_init(&in->hdlc_state, features);
		}
		st5481_usb_pipe_reset(in->adapter, in->ep, NULL, NULL);
		st5481_usb_device_ctrl_msg(in->adapter, in->counter,
					   in->packet_size,
					   NULL, NULL);
		st5481_start_rcv(in);
	} else {
		st5481_usb_device_ctrl_msg(in->adapter, in->counter,
					   0, NULL, NULL);
	}
}