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
#define  ND6_LLINFO_DELAY 134 
#define  ND6_LLINFO_INCOMPLETE 133 
#define  ND6_LLINFO_NOSTATE 132 
#define  ND6_LLINFO_PROBE 131 
#define  ND6_LLINFO_PURGE 130 
#define  ND6_LLINFO_REACHABLE 129 
#define  ND6_LLINFO_STALE 128 

const char *
ndcache_state2str(short ndp_state)
{
	const char *ndp_state_str = "UNKNOWN";
	switch (ndp_state) {
	case ND6_LLINFO_PURGE:
		ndp_state_str = "ND6_LLINFO_PURGE";
		break;
	case ND6_LLINFO_NOSTATE:
		ndp_state_str = "ND6_LLINFO_NOSTATE";
		break;
	case ND6_LLINFO_INCOMPLETE:
		ndp_state_str = "ND6_LLINFO_INCOMPLETE";
		break;
	case ND6_LLINFO_REACHABLE:
		ndp_state_str = "ND6_LLINFO_REACHABLE";
		break;
	case ND6_LLINFO_STALE:
		ndp_state_str = "ND6_LLINFO_STALE";
		break;
	case ND6_LLINFO_DELAY:
		ndp_state_str = "ND6_LLINFO_DELAY";
		break;
	case ND6_LLINFO_PROBE:
		ndp_state_str = "ND6_LLINFO_PROBE";
		break;
	default:
		/* Init'd to UNKNOWN */
		break;
	}
	return 	ndp_state_str;
}