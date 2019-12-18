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
typedef  enum fip_state { ____Placeholder_fip_state } fip_state ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 char** fcoe_ctlr_states ; 

__attribute__((used)) static const char *fcoe_ctlr_state(enum fip_state state)
{
	const char *cp = "unknown";

	if (state < ARRAY_SIZE(fcoe_ctlr_states))
		cp = fcoe_ctlr_states[state];
	if (!cp)
		cp = "unknown";
	return cp;
}