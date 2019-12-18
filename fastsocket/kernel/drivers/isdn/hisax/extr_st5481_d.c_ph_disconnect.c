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
struct st5481_adapter {int /*<<< orphan*/  leds; int /*<<< orphan*/  d_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  GREEN_LED ; 
 int /*<<< orphan*/  L1_MODE_NULL ; 
 int /*<<< orphan*/  st5481_in_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ph_disconnect(struct st5481_adapter *adapter)
{
	DBG(8,"");

	st5481_in_mode(&adapter->d_in, L1_MODE_NULL);

	// Turn off the green LED to tell that we left state F7
	adapter->leds &= ~GREEN_LED;
	st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, adapter->leds, NULL, NULL);
}