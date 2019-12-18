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
 scalar_t__ bfd_get_start_address (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  gr_checkin () ; 
 int /*<<< orphan*/  gr_clear_all_breakpoints () ; 
 int /*<<< orphan*/  gr_kill () ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  proceed (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_check_open () ; 

void
gr_create_inferior (char *execfile, char *args, char **env)
{
  int entry_pt;

  if (args && *args)
    error ("Can't pass arguments to remote process.");

  if (execfile == 0 || exec_bfd == 0)
    error ("No executable file specified");

  entry_pt = (int) bfd_get_start_address (exec_bfd);
  sr_check_open ();

  gr_kill ();
  gr_clear_all_breakpoints ();

  init_wait_for_inferior ();
  gr_checkin ();

  insert_breakpoints ();	/* Needed to get correct instruction in cache */
  proceed (entry_pt, -1, 0);
}