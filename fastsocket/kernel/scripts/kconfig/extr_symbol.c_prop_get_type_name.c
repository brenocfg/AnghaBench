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
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;

/* Variables and functions */
#define  P_CHOICE 136 
#define  P_COMMENT 135 
#define  P_DEFAULT 134 
#define  P_ENV 133 
#define  P_MENU 132 
#define  P_PROMPT 131 
#define  P_RANGE 130 
#define  P_SELECT 129 
#define  P_UNKNOWN 128 

const char *prop_get_type_name(enum prop_type type)
{
	switch (type) {
	case P_PROMPT:
		return "prompt";
	case P_ENV:
		return "env";
	case P_COMMENT:
		return "comment";
	case P_MENU:
		return "menu";
	case P_DEFAULT:
		return "default";
	case P_CHOICE:
		return "choice";
	case P_SELECT:
		return "select";
	case P_RANGE:
		return "range";
	case P_UNKNOWN:
		break;
	}
	return "unknown";
}