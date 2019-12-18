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
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  XenbusStateClosed 134 
#define  XenbusStateClosing 133 
#define  XenbusStateConnected 132 
#define  XenbusStateInitWait 131 
#define  XenbusStateInitialised 130 
#define  XenbusStateInitialising 129 
#define  XenbusStateUnknown 128 

const char *xenbus_strstate(enum xenbus_state state)
{
	static const char *const name[] = {
		[ XenbusStateUnknown      ] = "Unknown",
		[ XenbusStateInitialising ] = "Initialising",
		[ XenbusStateInitWait     ] = "InitWait",
		[ XenbusStateInitialised  ] = "Initialised",
		[ XenbusStateConnected    ] = "Connected",
		[ XenbusStateClosing      ] = "Closing",
		[ XenbusStateClosed	  ] = "Closed",
	};
	return (state < ARRAY_SIZE(name)) ? name[state] : "INVALID";
}