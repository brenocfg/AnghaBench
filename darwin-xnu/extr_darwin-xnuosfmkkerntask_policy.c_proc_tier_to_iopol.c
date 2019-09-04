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
 int IOPOL_DEFAULT ; 
 int IOPOL_PASSIVE ; 
 int IOPOL_STANDARD ; 
 int IOPOL_THROTTLE ; 
 int IOPOL_UTILITY ; 
#define  THROTTLE_LEVEL_NONE 132 
#define  THROTTLE_LEVEL_TIER0 131 
#define  THROTTLE_LEVEL_TIER1 130 
#define  THROTTLE_LEVEL_TIER2 129 
#define  THROTTLE_LEVEL_TIER3 128 
 int /*<<< orphan*/  panic (char*,int) ; 

int
proc_tier_to_iopol(int tier, int passive)
{
	if (passive == 1) {
		switch (tier) {
			case THROTTLE_LEVEL_TIER0:
				return IOPOL_PASSIVE;
			default:
				panic("unknown passive tier %d", tier);
				return IOPOL_DEFAULT;
		}
	} else {
		switch (tier) {
			case THROTTLE_LEVEL_NONE:
			case THROTTLE_LEVEL_TIER0:
				return IOPOL_DEFAULT;
			case THROTTLE_LEVEL_TIER1:
				return IOPOL_STANDARD;
			case THROTTLE_LEVEL_TIER2:
				return IOPOL_UTILITY;
			case THROTTLE_LEVEL_TIER3:
				return IOPOL_THROTTLE;
			default:
				panic("unknown tier %d", tier);
				return IOPOL_DEFAULT;
		}
	}
}