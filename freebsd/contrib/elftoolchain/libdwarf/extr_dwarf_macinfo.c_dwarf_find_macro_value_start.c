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

char *
dwarf_find_macro_value_start(char *macro_string)
{
	char *p;

	if (macro_string == NULL)
		return (NULL);

	p = macro_string;
	while (*p != '\0' && *p != ' ')
		p++;
	if (*p == ' ')
		p++;

	return (p);
}