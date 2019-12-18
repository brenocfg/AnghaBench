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
typedef  int u8 ;

/* Variables and functions */
 int BT_MASK ; 
 int /*<<< orphan*/  COMPAL_EC_COMMAND_WIRELESS ; 
 int KILLSWITCH_MASK ; 
 int WLAN_MASK ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_wireless_state(int *wlan, int *bluetooth)
{
	u8 result;

	ec_read(COMPAL_EC_COMMAND_WIRELESS, &result);

	if (wlan) {
		if ((result & KILLSWITCH_MASK) == 0)
			*wlan = 0;
		else
			*wlan = result & WLAN_MASK;
	}

	if (bluetooth) {
		if ((result & KILLSWITCH_MASK) == 0)
			*bluetooth = 0;
		else
			*bluetooth = (result & BT_MASK) >> 1;
	}

	return 0;
}