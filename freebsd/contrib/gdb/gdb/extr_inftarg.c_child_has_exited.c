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
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 

int
child_has_exited (int pid, int wait_status, int *exit_status)
{
  if (WIFEXITED (wait_status))
    {
      *exit_status = WEXITSTATUS (wait_status);
      return 1;
    }

  if (WIFSIGNALED (wait_status))
    {
      *exit_status = 0;		/* ?? Don't know what else to say here. */
      return 1;
    }

  /* ?? Do we really need to consult the event state, too?  Assume the
     wait_state alone suffices.
   */
  return 0;
}