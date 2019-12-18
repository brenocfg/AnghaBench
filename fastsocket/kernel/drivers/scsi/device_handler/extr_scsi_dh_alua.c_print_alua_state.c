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
#define  TPGS_STATE_LBA_DEPENDENT 134 
#define  TPGS_STATE_NONOPTIMIZED 133 
#define  TPGS_STATE_OFFLINE 132 
#define  TPGS_STATE_OPTIMIZED 131 
#define  TPGS_STATE_STANDBY 130 
#define  TPGS_STATE_TRANSITIONING 129 
#define  TPGS_STATE_UNAVAILABLE 128 

__attribute__((used)) static char print_alua_state(int state)
{
	switch (state) {
	case TPGS_STATE_OPTIMIZED:
		return 'A';
	case TPGS_STATE_NONOPTIMIZED:
		return 'N';
	case TPGS_STATE_STANDBY:
		return 'S';
	case TPGS_STATE_UNAVAILABLE:
		return 'U';
	case TPGS_STATE_LBA_DEPENDENT:
		return 'L';
	case TPGS_STATE_OFFLINE:
		return 'O';
	case TPGS_STATE_TRANSITIONING:
		return 'T';
	default:
		return 'X';
	}
}