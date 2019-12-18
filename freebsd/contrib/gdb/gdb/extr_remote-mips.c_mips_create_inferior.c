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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 scalar_t__ bfd_get_start_address (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  execute_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  proceed (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
mips_create_inferior (char *execfile, char *args, char **env)
{
  CORE_ADDR entry_pt;

  if (args && *args)
    {
      warning ("\
Can't pass arguments to remote MIPS board; arguments ignored.");
      /* And don't try to use them on the next "run" command.  */
      execute_command ("set args", 0);
    }

  if (execfile == 0 || exec_bfd == 0)
    error ("No executable file specified");

  entry_pt = (CORE_ADDR) bfd_get_start_address (exec_bfd);

  init_wait_for_inferior ();

  /* FIXME: Should we set inferior_ptid here?  */

  proceed (entry_pt, TARGET_SIGNAL_DEFAULT, 0);
}