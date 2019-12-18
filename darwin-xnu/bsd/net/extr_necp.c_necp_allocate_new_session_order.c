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
typedef  int u_int32_t ;
typedef  int control_unit ;

/* Variables and functions */
 int NECP_SESSION_NUM_PRIORITIES ; 
 int NECP_SESSION_PRIORITY_DEFAULT ; 
 int NECP_SESSION_PRIORITY_UNKNOWN ; 

__attribute__((used)) static u_int32_t
necp_allocate_new_session_order(u_int32_t priority, u_int32_t control_unit)
{
	u_int32_t new_order = 0;

	// For now, just allocate 1000 orders for each priority
	if (priority == NECP_SESSION_PRIORITY_UNKNOWN || priority > NECP_SESSION_NUM_PRIORITIES) {
		priority = NECP_SESSION_PRIORITY_DEFAULT;
	}

	// Use the control unit to decide the offset into the priority list
	new_order = (control_unit) + ((priority - 1) * 1000);

	return (new_order);
}