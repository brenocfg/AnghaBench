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
 int simple_strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_range(char **str, int *pint)
{
	int x, inc_counter, upper_range;

	(*str)++;
	upper_range = simple_strtol((*str), NULL, 0);
	inc_counter = upper_range - *pint;
	for (x = *pint; x < upper_range; x++)
		*pint++ = x;
	return inc_counter;
}