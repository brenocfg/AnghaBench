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
typedef  int u16 ;

/* Variables and functions */
#define  HFA384X_LINKSTATUS_AP_CHANGE 133 
#define  HFA384X_LINKSTATUS_AP_IN_RANGE 132 
#define  HFA384X_LINKSTATUS_AP_OUT_OF_RANGE 131 
#define  HFA384X_LINKSTATUS_ASSOC_FAILED 130 
#define  HFA384X_LINKSTATUS_CONNECTED 129 
#define  HFA384X_LINKSTATUS_DISCONNECTED 128 

__attribute__((used)) static const char* hfa384x_linkstatus_str(u16 linkstatus)
{
	switch (linkstatus) {
	case HFA384X_LINKSTATUS_CONNECTED:
		return "Connected";
	case HFA384X_LINKSTATUS_DISCONNECTED:
		return "Disconnected";
	case HFA384X_LINKSTATUS_AP_CHANGE:
		return "Access point change";
	case HFA384X_LINKSTATUS_AP_OUT_OF_RANGE:
		return "Access point out of range";
	case HFA384X_LINKSTATUS_AP_IN_RANGE:
		return "Access point in range";
	case HFA384X_LINKSTATUS_ASSOC_FAILED:
		return "Association failed";
	default:
		return "Unknown";
	}
}