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
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED 132 
#define  ALUA_ACCESS_STATE_ACTIVE_OPTMIZED 131 
#define  ALUA_ACCESS_STATE_OFFLINE 130 
#define  ALUA_ACCESS_STATE_STANDBY 129 
#define  ALUA_ACCESS_STATE_UNAVAILABLE 128 
 int /*<<< orphan*/  TCM_INVALID_PARAMETER_LIST ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static sense_reason_t
core_alua_check_transition(int state, int *primary)
{
	switch (state) {
	case ALUA_ACCESS_STATE_ACTIVE_OPTMIZED:
	case ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
	case ALUA_ACCESS_STATE_STANDBY:
	case ALUA_ACCESS_STATE_UNAVAILABLE:
		/*
		 * OPTIMIZED, NON-OPTIMIZED, STANDBY and UNAVAILABLE are
		 * defined as primary target port asymmetric access states.
		 */
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_OFFLINE:
		/*
		 * OFFLINE state is defined as a secondary target port
		 * asymmetric access state.
		 */
		*primary = 0;
		break;
	default:
		pr_err("Unknown ALUA access state: 0x%02x\n", state);
		return TCM_INVALID_PARAMETER_LIST;
	}

	return 0;
}