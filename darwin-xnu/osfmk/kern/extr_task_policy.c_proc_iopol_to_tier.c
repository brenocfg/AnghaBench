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
#define  IOPOL_IMPORTANT 132 
#define  IOPOL_PASSIVE 131 
#define  IOPOL_STANDARD 130 
#define  IOPOL_THROTTLE 129 
#define  IOPOL_UTILITY 128 
 int THROTTLE_LEVEL_TIER0 ; 
 int THROTTLE_LEVEL_TIER1 ; 
 int THROTTLE_LEVEL_TIER2 ; 
 int THROTTLE_LEVEL_TIER3 ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
proc_iopol_to_tier(int iopolicy, int *tier, int *passive)
{
	*passive = 0;
	*tier = 0;
	switch (iopolicy) {
		case IOPOL_IMPORTANT:
			*tier = THROTTLE_LEVEL_TIER0;
			break;
		case IOPOL_PASSIVE:
			*tier = THROTTLE_LEVEL_TIER0;
			*passive = 1;
			break;
		case IOPOL_STANDARD:
			*tier = THROTTLE_LEVEL_TIER1;
			break;
		case IOPOL_UTILITY:
			*tier = THROTTLE_LEVEL_TIER2;
			break;
		case IOPOL_THROTTLE:
			*tier = THROTTLE_LEVEL_TIER3;
			break;
		default:
			panic("unknown I/O policy %d", iopolicy);
			break;
	}
}