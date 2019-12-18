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

__attribute__((used)) static int
for_var_len(const char *var)
{
    char ch, var_start, var_end;
    int depth;
    int len;

    var_start = *var;
    if (var_start == 0)
	/* just escape the $ */
	return 0;

    if (var_start == '(')
	var_end = ')';
    else if (var_start == '{')
	var_end = '}';
    else
	/* Single char variable */
	return 1;

    depth = 1;
    for (len = 1; (ch = var[len++]) != 0;) {
	if (ch == var_start)
	    depth++;
	else if (ch == var_end && --depth == 0)
	    return len;
    }

    /* Variable end not found, escape the $ */
    return 0;
}