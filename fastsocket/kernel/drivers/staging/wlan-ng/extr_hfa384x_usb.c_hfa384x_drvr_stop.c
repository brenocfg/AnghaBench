#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* port_enabled; int /*<<< orphan*/  commsqual_timer; int /*<<< orphan*/  state; int /*<<< orphan*/  link_status; int /*<<< orphan*/  rx_urb; TYPE_1__* wlandev; } ;
typedef  TYPE_2__ hfa384x_t ;
struct TYPE_5__ {int /*<<< orphan*/  hwremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_LINK_NOTCONNECTED ; 
 int HFA384x_NUMPORTS_MAX ; 
 int /*<<< orphan*/  HFA384x_STATE_INIT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfa384x_cmd_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

int hfa384x_drvr_stop(hfa384x_t *hw)
{
	int result = 0;
	int i;

	might_sleep();

	/* There's no need for spinlocks here. The USB "disconnect"
	 * function sets this "removed" flag and then calls us.
	 */
	if (!hw->wlandev->hwremoved) {
		/* Call initialize to leave the MAC in its 'reset' state */
		hfa384x_cmd_initialize(hw);

		/* Cancel the rxurb */
		usb_kill_urb(&hw->rx_urb);
	}

	hw->link_status = HFA384x_LINK_NOTCONNECTED;
	hw->state = HFA384x_STATE_INIT;

	del_timer_sync(&hw->commsqual_timer);

	/* Clear all the port status */
	for (i = 0; i < HFA384x_NUMPORTS_MAX; i++)
		hw->port_enabled[i] = 0;

	return result;
}