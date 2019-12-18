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
 size_t counter ; 
 int /*<<< orphan*/  cs_close (void*) ; 
 scalar_t__ e_flag ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * function ; 
 int /*<<< orphan*/ * list_lines ; 
 size_t size_lines ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int teardown_issue(void **state)
{
	if (e_flag == 0)
		while (counter < size_lines && strncmp(list_lines[counter], "!# ", 3))
			counter++;
	else
		while (counter < size_lines && strncmp(list_lines[counter], "// !# ", 6))
			counter++;

	cs_close(*state);
	free(*state);
	function = NULL;
	return 0;
}