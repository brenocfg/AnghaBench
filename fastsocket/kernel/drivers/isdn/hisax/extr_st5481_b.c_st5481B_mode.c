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
struct st5481_b_out {int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  hdlc_state; scalar_t__ busy; int /*<<< orphan*/ * urb; } ;
struct st5481_bcs {int channel; int mode; int /*<<< orphan*/  b_in; struct st5481_adapter* adapter; struct st5481_b_out b_out; } ;
struct st5481_adapter {int number_of_leds; int leds; } ;

/* Variables and functions */
 int B1_LED ; 
 int B2_LED ; 
 int /*<<< orphan*/  DBG (int,char*,int,int) ; 
 scalar_t__ FFMSK_B1 ; 
 scalar_t__ GPIO_OUT ; 
 int /*<<< orphan*/  HDLC_56KBIT ; 
 int /*<<< orphan*/  HDLC_BITREVERSE ; 
 int L1_MODE_HDLC_56K ; 
 int L1_MODE_NULL ; 
 int L1_MODE_TRANS ; 
 scalar_t__ OUT_B1_COUNTER ; 
 int OUT_DOWN ; 
 int OUT_UNDERRUN ; 
 int OUT_UP ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdnhdlc_out_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * st5481B_start_xfer ; 
 int /*<<< orphan*/  st5481_in_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,scalar_t__,int,int /*<<< orphan*/ *,struct st5481_bcs*) ; 
 int /*<<< orphan*/  st5481_usb_pipe_reset (struct st5481_adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st5481B_mode(struct st5481_bcs *bcs, int mode)
{
	struct st5481_b_out *b_out = &bcs->b_out;
	struct st5481_adapter *adapter = bcs->adapter;

	DBG(4,"B%d,mode=%d", bcs->channel + 1, mode);

	if (bcs->mode == mode)
		return;

	bcs->mode = mode;

	// Cancel all USB transfers on this B channel
	usb_unlink_urb(b_out->urb[0]);
	usb_unlink_urb(b_out->urb[1]);
	b_out->busy = 0;

	st5481_in_mode(&bcs->b_in, mode);
	if (bcs->mode != L1_MODE_NULL) {
		// Open the B channel
		if (bcs->mode != L1_MODE_TRANS) {
			u32 features = HDLC_BITREVERSE;
			if (bcs->mode == L1_MODE_HDLC_56K)
				features |= HDLC_56KBIT;
			isdnhdlc_out_init(&b_out->hdlc_state, features);
		}
		st5481_usb_pipe_reset(adapter, (bcs->channel+1)*2, NULL, NULL);
	
		// Enable B channel interrupts
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1+(bcs->channel*2), 
				    OUT_UP+OUT_DOWN+OUT_UNDERRUN, NULL, NULL);

		// Enable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel*2), 32, st5481B_start_xfer, bcs);
		if (adapter->number_of_leds == 4) {
			if (bcs->channel == 0) {
				adapter->leds |= B1_LED;
			} else {
				adapter->leds |= B2_LED;
			}
		}
	} else {
		// Disble B channel interrupts
		st5481_usb_device_ctrl_msg(adapter, FFMSK_B1+(bcs->channel*2), 0, NULL, NULL);

		// Disable B channel FIFOs
		st5481_usb_device_ctrl_msg(adapter, OUT_B1_COUNTER+(bcs->channel*2), 0, NULL, NULL);

		if (adapter->number_of_leds == 4) {
			if (bcs->channel == 0) {
				adapter->leds &= ~B1_LED;
			} else {
				adapter->leds &= ~B2_LED;
			}
		} else {
			st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, adapter->leds, NULL, NULL);
		}
		if (b_out->tx_skb) {
			dev_kfree_skb_any(b_out->tx_skb);
			b_out->tx_skb = NULL;
		}
		
	}
}