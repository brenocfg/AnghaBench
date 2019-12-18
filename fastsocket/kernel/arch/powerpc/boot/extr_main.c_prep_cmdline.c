#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* edit_cmdline ) (char*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ COMMAND_LINE_SIZE ; 
 char* cmdline ; 
 TYPE_1__ console_ops ; 
 int /*<<< orphan*/  getprop (void*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setprop_str (void*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,scalar_t__) ; 

__attribute__((used)) static void prep_cmdline(void *chosen)
{
	if (cmdline[0] == '\0')
		getprop(chosen, "bootargs", cmdline, COMMAND_LINE_SIZE-1);

	printf("\n\rLinux/PowerPC load: %s", cmdline);
	/* If possible, edit the command line */
	if (console_ops.edit_cmdline)
		console_ops.edit_cmdline(cmdline, COMMAND_LINE_SIZE);
	printf("\n\r");

	/* Put the command line back into the devtree for the kernel */
	setprop_str(chosen, "bootargs", cmdline);
}