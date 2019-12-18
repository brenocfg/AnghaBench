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
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  error (char*) ; 
 int fprint_target_auxv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  target_has_stack ; 

__attribute__((used)) static void
info_auxv_command (char *cmd, int from_tty)
{
  if (! target_has_stack)
    error ("The program has no auxiliary information now.");
  else
    {
      int ents = fprint_target_auxv (gdb_stdout, &current_target);
      if (ents < 0)
	error ("No auxiliary vector found, or failed reading it.");
      else if (ents == 0)
	error ("Auxiliary vector is empty.");
    }
}