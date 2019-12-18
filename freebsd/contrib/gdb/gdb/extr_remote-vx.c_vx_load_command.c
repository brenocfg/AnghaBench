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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  immediate_quit ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int net_load (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  vx_add_symbols (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
vx_load_command (char *arg_string, int from_tty)
{
  CORE_ADDR text_addr;
  CORE_ADDR data_addr;
  CORE_ADDR bss_addr;

  if (arg_string == 0)
    error ("The load command takes a file name");

  arg_string = tilde_expand (arg_string);
  make_cleanup (xfree, arg_string);

  dont_repeat ();

  /* Refuse to load the module if a debugged task is running.  Doing so
     can have a number of unpleasant consequences to the running task.  */

  if (PIDGET (inferior_ptid) != 0 && target_has_execution)
    {
      if (query ("You may not load a module while the target task is running.\n\
Kill the target task? "))
	target_kill ();
      else
	error ("Load canceled.");
    }

  QUIT;
  immediate_quit++;
  if (net_load (arg_string, &text_addr, &data_addr, &bss_addr) == -1)
    error ("Load failed on target machine");
  immediate_quit--;

  vx_add_symbols (arg_string, from_tty, text_addr, data_addr, bss_addr);

  /* Getting new symbols may change our opinion about what is
     frameless.  */
  reinit_frame_cache ();
}