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
struct inf {scalar_t__ signal_thread; } ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ inf_tid_to_thread (struct inf*,int) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  thread_id_to_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_sig_thread_cmd (char *args, int from_tty)
{
  struct inf *inf = cur_inf ();

  if (!args || (!isdigit (*args) && strcmp (args, "none") != 0))
    error ("Illegal argument to \"set signal-thread\" command.\n"
	   "Should be an integer thread ID, or `none'.");

  if (strcmp (args, "none") == 0)
    inf->signal_thread = 0;
  else
    {
      int tid = PIDGET (thread_id_to_pid (atoi (args)));
      if (tid < 0)
	error ("Thread ID %s not known.  Use the \"info threads\" command to\n"
	       "see the IDs of currently known threads.", args);
      inf->signal_thread = inf_tid_to_thread (inf, tid);
    }
}