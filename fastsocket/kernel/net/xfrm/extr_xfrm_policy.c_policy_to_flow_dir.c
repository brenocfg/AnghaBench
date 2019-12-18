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
 scalar_t__ FLOW_DIR_FWD ; 
 scalar_t__ FLOW_DIR_IN ; 
 scalar_t__ FLOW_DIR_OUT ; 
#define  XFRM_POLICY_FWD 130 
#define  XFRM_POLICY_IN 129 
#define  XFRM_POLICY_OUT 128 

__attribute__((used)) static inline int policy_to_flow_dir(int dir)
{
	if (XFRM_POLICY_IN == FLOW_DIR_IN &&
	    XFRM_POLICY_OUT == FLOW_DIR_OUT &&
	    XFRM_POLICY_FWD == FLOW_DIR_FWD)
		return dir;
	switch (dir) {
	default:
	case XFRM_POLICY_IN:
		return FLOW_DIR_IN;
	case XFRM_POLICY_OUT:
		return FLOW_DIR_OUT;
	case XFRM_POLICY_FWD:
		return FLOW_DIR_FWD;
	}
}