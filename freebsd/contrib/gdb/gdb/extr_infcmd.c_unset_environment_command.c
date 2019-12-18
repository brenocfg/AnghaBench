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
 int /*<<< orphan*/  free_environ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_environ ; 
 int /*<<< orphan*/  make_environ () ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  unset_in_environ (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
unset_environment_command (char *var, int from_tty)
{
  if (var == 0)
    {
      /* If there is no argument, delete all environment variables.
         Ask for confirmation if reading from the terminal.  */
      if (!from_tty || query ("Delete all environment variables? "))
	{
	  free_environ (inferior_environ);
	  inferior_environ = make_environ ();
	}
    }
  else
    unset_in_environ (inferior_environ, var);
}