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
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int const NUM_RFKILL_TYPES ; 
#define  RFKILL_TYPE_BLUETOOTH 133 
#define  RFKILL_TYPE_GPS 132 
#define  RFKILL_TYPE_UWB 131 
#define  RFKILL_TYPE_WIMAX 130 
#define  RFKILL_TYPE_WLAN 129 
#define  RFKILL_TYPE_WWAN 128 

__attribute__((used)) static const char *rfkill_get_type_str(enum rfkill_type type)
{
	switch (type) {
	case RFKILL_TYPE_WLAN:
		return "wlan";
	case RFKILL_TYPE_BLUETOOTH:
		return "bluetooth";
	case RFKILL_TYPE_UWB:
		return "ultrawideband";
	case RFKILL_TYPE_WIMAX:
		return "wimax";
	case RFKILL_TYPE_WWAN:
		return "wwan";
	case RFKILL_TYPE_GPS:
		return "gps";
	default:
		BUG();
	}

	BUILD_BUG_ON(NUM_RFKILL_TYPES != RFKILL_TYPE_GPS + 1);
}