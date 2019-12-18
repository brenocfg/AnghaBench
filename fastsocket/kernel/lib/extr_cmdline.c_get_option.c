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
 int simple_strtol (char*,char**,int /*<<< orphan*/ ) ; 

int get_option (char **str, int *pint)
{
	char *cur = *str;

	if (!cur || !(*cur))
		return 0;
	*pint = simple_strtol (cur, str, 0);
	if (cur == *str)
		return 0;
	if (**str == ',') {
		(*str)++;
		return 2;
	}
	if (**str == '-')
		return 3;

	return 1;
}