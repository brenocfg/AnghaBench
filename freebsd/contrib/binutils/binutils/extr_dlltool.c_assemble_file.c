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
 char* ASM_SWITCHES ; 
 scalar_t__ alloca (scalar_t__) ; 
 char* as_flags ; 
 int /*<<< orphan*/  as_name ; 
 int /*<<< orphan*/  run (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
assemble_file (const char * source, const char * dest)
{
  char * cmd;

  cmd = (char *) alloca (strlen (ASM_SWITCHES) + strlen (as_flags)
			 + strlen (source) + strlen (dest) + 50);

  sprintf (cmd, "%s %s -o %s %s", ASM_SWITCHES, as_flags, dest, source);

  run (as_name, cmd);
}