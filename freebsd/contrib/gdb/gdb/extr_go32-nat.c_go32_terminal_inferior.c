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
 int /*<<< orphan*/  child_cmd ; 
 int /*<<< orphan*/  device_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ inf_mode_valid ; 
 int /*<<< orphan*/  inf_terminal_mode ; 
 int redir_to_child (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redir_to_debugger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 scalar_t__ terminal_is_ours ; 

__attribute__((used)) static void
go32_terminal_inferior (void)
{
  /* Redirect standard handles as child wants them.  */
  errno = 0;
  if (redir_to_child (&child_cmd) == -1)
  {
    redir_to_debugger (&child_cmd);
    error ("Cannot redirect standard handles for program: %s.",
	   safe_strerror (errno));
  }
  /* set the console device of the inferior to whatever mode
     (raw or cooked) we found it last time */
  if (terminal_is_ours)
  {
    if (inf_mode_valid)
      device_mode (0, inf_terminal_mode);
    terminal_is_ours = 0;
  }
}