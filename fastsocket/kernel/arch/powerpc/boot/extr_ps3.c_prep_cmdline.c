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
 scalar_t__ COMMAND_LINE_SIZE ; 
 char* cmdline ; 
 int /*<<< orphan*/  getprop (void*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setprop_str (void*,char*,char*) ; 

__attribute__((used)) static void prep_cmdline(void *chosen)
{
	if (cmdline[0] == '\0')
		getprop(chosen, "bootargs", cmdline, COMMAND_LINE_SIZE-1);
	else
		setprop_str(chosen, "bootargs", cmdline);

	printf("cmdline: '%s'\n", cmdline);
}