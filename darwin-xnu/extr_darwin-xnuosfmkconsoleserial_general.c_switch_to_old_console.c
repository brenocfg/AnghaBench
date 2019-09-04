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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 scalar_t__ cons_ops_index ; 
 scalar_t__ nconsops ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

void
switch_to_old_console(int old_console)
{
	static boolean_t squawked;
	uint32_t ops = old_console;

	if ((ops >= nconsops) && !squawked) {
		squawked = TRUE;
		printf("switch_to_old_console: unknown ops %d\n", ops);
	} else
		cons_ops_index = ops;
}