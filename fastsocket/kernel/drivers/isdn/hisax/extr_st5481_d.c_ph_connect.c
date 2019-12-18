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
struct st5481_in {int dummy; } ;
struct st5481_d_out {int /*<<< orphan*/  fsm; } ;
struct st5481_adapter {int leds; struct st5481_in d_in; struct st5481_d_out d_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int EP_D_OUT ; 
 int /*<<< orphan*/  FFMSK_D ; 
 int /*<<< orphan*/  FsmChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int GREEN_LED ; 
 int /*<<< orphan*/  L1_MODE_HDLC ; 
 int /*<<< orphan*/  LBB ; 
 int /*<<< orphan*/  ST_DOUT_NONE ; 
 int USB_DIR_OUT ; 
 struct st5481_adapter* cs ; 
 int /*<<< orphan*/  st5481_in_mode (struct st5481_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5481_usb_pipe_reset (struct st5481_adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ph_connect(struct st5481_adapter *adapter)
{
	struct st5481_d_out *d_out = &adapter->d_out;
	struct st5481_in *d_in = &adapter->d_in;

	DBG(8,"");
		
	FsmChangeState(&d_out->fsm, ST_DOUT_NONE);

	//	st5481_usb_device_ctrl_msg(adapter, FFMSK_D, OUT_UNDERRUN, NULL, NULL);
	st5481_usb_device_ctrl_msg(adapter, FFMSK_D, 0xfc, NULL, NULL);
	st5481_in_mode(d_in, L1_MODE_HDLC);

#ifdef LOOPBACK
	// Turn loopback on (data sent on B and D looped back)
	st5481_usb_device_ctrl_msg(cs, LBB, 0x04, NULL, NULL);
#endif

	st5481_usb_pipe_reset(adapter, EP_D_OUT | USB_DIR_OUT, NULL, NULL);

	// Turn on the green LED to tell that we are in state F7
	adapter->leds |= GREEN_LED;
	st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, adapter->leds, NULL, NULL);
}