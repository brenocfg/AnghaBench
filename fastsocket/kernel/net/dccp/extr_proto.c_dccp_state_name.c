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

/* Variables and functions */
#define  DCCP_ACTIVE_CLOSEREQ 138 
#define  DCCP_CLOSED 137 
#define  DCCP_CLOSING 136 
#define  DCCP_LISTEN 135 
 int const DCCP_MAX_STATES ; 
#define  DCCP_OPEN 134 
#define  DCCP_PARTOPEN 133 
#define  DCCP_PASSIVE_CLOSE 132 
#define  DCCP_PASSIVE_CLOSEREQ 131 
#define  DCCP_REQUESTING 130 
#define  DCCP_RESPOND 129 
#define  DCCP_TIME_WAIT 128 

const char *dccp_state_name(const int state)
{
	static const char *const dccp_state_names[] = {
	[DCCP_OPEN]		= "OPEN",
	[DCCP_REQUESTING]	= "REQUESTING",
	[DCCP_PARTOPEN]		= "PARTOPEN",
	[DCCP_LISTEN]		= "LISTEN",
	[DCCP_RESPOND]		= "RESPOND",
	[DCCP_CLOSING]		= "CLOSING",
	[DCCP_ACTIVE_CLOSEREQ]	= "CLOSEREQ",
	[DCCP_PASSIVE_CLOSE]	= "PASSIVE_CLOSE",
	[DCCP_PASSIVE_CLOSEREQ]	= "PASSIVE_CLOSEREQ",
	[DCCP_TIME_WAIT]	= "TIME_WAIT",
	[DCCP_CLOSED]		= "CLOSED",
	};

	if (state >= DCCP_MAX_STATES)
		return "INVALID STATE!";
	else
		return dccp_state_names[state];
}