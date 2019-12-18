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
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  proceed (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_set_command_line (char*,char*) ; 
 int /*<<< orphan*/  remote_rdp_kill () ; 
 int /*<<< orphan*/  remove_breakpoints () ; 

__attribute__((used)) static void
remote_rdp_create_inferior (char *exec_file, char *allargs, char **env)
{
  CORE_ADDR entry_point;

  if (exec_file == 0 || exec_bfd == 0)
    error ("No executable file specified.");

  entry_point = (CORE_ADDR) bfd_get_start_address (exec_bfd);

  remote_rdp_kill ();
  remove_breakpoints ();
  init_wait_for_inferior ();

  /* This gives us a chance to set up the command line */
  rdp_set_command_line (exec_file, allargs);

  inferior_ptid = pid_to_ptid (42);
  insert_breakpoints ();	/* Needed to get correct instruction in cache */

  /*
     ** RDP targets don't provide any facility to set the top of memory,
     ** so we don't bother to look for MEMSIZE in the environment.
   */

  /* Let's go! */
  proceed (entry_point, TARGET_SIGNAL_DEFAULT, 0);
}