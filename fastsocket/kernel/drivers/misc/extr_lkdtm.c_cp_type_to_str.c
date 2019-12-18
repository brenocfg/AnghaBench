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
typedef  enum ctype { ____Placeholder_ctype } ctype ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int CT_NONE ; 
 char const** cp_type ; 

__attribute__((used)) static const char *cp_type_to_str(enum ctype type)
{
	if (type == CT_NONE || type < 0 || type > ARRAY_SIZE(cp_type))
		return "None";

	return cp_type[type - 1];
}