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
typedef  int /*<<< orphan*/  u_char ;
struct st5481_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  ctrl_complete_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int /*<<< orphan*/  USB_REQ_CLEAR_FEATURE ; 
 int /*<<< orphan*/  usb_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void st5481_usb_pipe_reset(struct st5481_adapter *adapter,
		    u_char pipe,
		    ctrl_complete_t complete, void *context)
{
	DBG(1,"pipe=%02x",pipe);

	usb_ctrl_msg(adapter,
		     USB_REQ_CLEAR_FEATURE, USB_DIR_OUT | USB_RECIP_ENDPOINT,
		     0, pipe, complete, context);
}