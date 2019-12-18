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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int CT_NONE ; 
 int /*<<< orphan*/ * cp_type ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ctype parse_cp_type(const char *what, size_t count)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cp_type); i++) {
		if (!strcmp(what, cp_type[i]))
			return i + 1;
	}

	return CT_NONE;
}