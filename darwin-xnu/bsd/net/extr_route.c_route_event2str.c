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
#define  ROUTE_ENTRY_DELETED 139 
#define  ROUTE_ENTRY_REFRESH 138 
#define  ROUTE_EVHDLR_DEREGISTER 137 
#define  ROUTE_LLENTRY_CHANGED 136 
#define  ROUTE_LLENTRY_DELETED 135 
#define  ROUTE_LLENTRY_EXPIRED 134 
#define  ROUTE_LLENTRY_PROBED 133 
#define  ROUTE_LLENTRY_RESOLVED 132 
#define  ROUTE_LLENTRY_STALE 131 
#define  ROUTE_LLENTRY_TIMEDOUT 130 
#define  ROUTE_LLENTRY_UNREACH 129 
#define  ROUTE_STATUS_UPDATE 128 

const char *
route_event2str(int route_event)
{
	const char *route_event_str = "ROUTE_EVENT_UNKNOWN";
	switch (route_event) {
		case ROUTE_STATUS_UPDATE:
			route_event_str = "ROUTE_STATUS_UPDATE";
			break;
		case ROUTE_ENTRY_REFRESH:
			route_event_str = "ROUTE_ENTRY_REFRESH";
			break;
		case ROUTE_ENTRY_DELETED:
			route_event_str = "ROUTE_ENTRY_DELETED";
			break;
		case ROUTE_LLENTRY_RESOLVED:
			route_event_str = "ROUTE_LLENTRY_RESOLVED";
			break;
		case ROUTE_LLENTRY_UNREACH:
			route_event_str = "ROUTE_LLENTRY_UNREACH";
			break;
		case ROUTE_LLENTRY_CHANGED:
			route_event_str = "ROUTE_LLENTRY_CHANGED";
			break;
		case ROUTE_LLENTRY_STALE:
			route_event_str = "ROUTE_LLENTRY_STALE";
			break;
		case ROUTE_LLENTRY_TIMEDOUT:
			route_event_str = "ROUTE_LLENTRY_TIMEDOUT";
			break;
		case ROUTE_LLENTRY_DELETED:
			route_event_str = "ROUTE_LLENTRY_DELETED";
			break;
		case ROUTE_LLENTRY_EXPIRED:
			route_event_str = "ROUTE_LLENTRY_EXPIRED";
			break;
		case ROUTE_LLENTRY_PROBED:
			route_event_str = "ROUTE_LLENTRY_PROBED";
			break;
		case ROUTE_EVHDLR_DEREGISTER:
			route_event_str = "ROUTE_EVHDLR_DEREGISTER";
			break;
		default:
			/* Init'd to ROUTE_EVENT_UNKNOWN */
			break;
	}
	return  route_event_str;
}