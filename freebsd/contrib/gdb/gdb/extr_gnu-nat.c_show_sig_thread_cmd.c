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
 struct inf* active_inf () ; 
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  proc_string (scalar_t__) ; 

__attribute__((used)) static void
show_sig_thread_cmd (char *args, int from_tty)
{
  struct inf *inf = active_inf ();
  check_empty (args, "show signal-thread");
  if (inf->signal_thread)
    printf_unfiltered ("The signal thread is %s.\n",
		       proc_string (inf->signal_thread));
  else
    printf_unfiltered ("There is no signal thread.\n");
}