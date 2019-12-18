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
#define  MPC 131 
#define  MPS 130 
#define  MPS_AND_MPC 129 
#define  NON_MPOA 128 

__attribute__((used)) static const char *mpoa_device_type_string(char type)
{
	switch(type) {
	case NON_MPOA:
		return "non-MPOA device";
		break;
	case MPS:
		return "MPS";
		break;
	case MPC:
		return "MPC";
		break;
	case MPS_AND_MPC:
		return "both MPS and MPC";
		break;
	default:
		return "unspecified (non-MPOA) device";
		break;
	}

	return ""; /* not reached */
}