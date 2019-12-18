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
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPERM ; 
#define  NECP_ERROR_INTERNAL 135 
#define  NECP_ERROR_INVALID_PROCESS 134 
#define  NECP_ERROR_INVALID_TLV 133 
#define  NECP_ERROR_POLICY_CONDITIONS_INVALID 132 
#define  NECP_ERROR_POLICY_ID_NOT_FOUND 131 
#define  NECP_ERROR_POLICY_RESULT_INVALID 130 
#define  NECP_ERROR_ROUTE_RULES_INVALID 129 
#define  NECP_ERROR_UNKNOWN_PACKET_TYPE 128 

__attribute__((used)) static int
necp_get_posix_error_for_necp_error(int response_error)
{
	switch (response_error) {
		case NECP_ERROR_UNKNOWN_PACKET_TYPE:
		case NECP_ERROR_INVALID_TLV:
		case NECP_ERROR_POLICY_RESULT_INVALID:
		case NECP_ERROR_POLICY_CONDITIONS_INVALID:
		case NECP_ERROR_ROUTE_RULES_INVALID: {
			return (EINVAL);
		}
		case NECP_ERROR_POLICY_ID_NOT_FOUND: {
			return (ENOENT);
		}
		case NECP_ERROR_INVALID_PROCESS: {
			return (EPERM);
		}
		case NECP_ERROR_INTERNAL:
		default: {
			return (ENOMEM);
		}
	}
}