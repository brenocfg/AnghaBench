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
 int /*<<< orphan*/ * commandline ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ **,char*,char*,char*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rdp_set_command_line (char *command, char *args)
{
  /*
     ** We could use RDP_INFO_SET_CMDLINE to send this, but EmbeddedICE systems
     ** don't implement that, and get all confused at the unexpected text.
     ** Instead, just keep a copy, and send it when the target does a SWI_GetEnv
   */

  if (commandline != NULL)
    xfree (commandline);

  xasprintf (&commandline, "%s %s", command, args);
}