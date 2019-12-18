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
 scalar_t__ FALSE ; 
 scalar_t__ MONITOR_break_brk ; 
 scalar_t__ TRUE ; 
 scalar_t__ Util_stricmp (char*,char*) ; 
 char* get_token () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void monitor_break_BRK(void)
{
	char *t = get_token();
	if (t == NULL)
		printf("Break on BRK is %sabled\n", MONITOR_break_brk ? "en" : "dis");
	else if (Util_stricmp(t, "ON") == 0)
		MONITOR_break_brk = TRUE;
	else if (Util_stricmp(t, "OFF") == 0)
		MONITOR_break_brk = FALSE;
	else
		printf("Invalid argument. Usage: BBRK ON or OFF\n");
}