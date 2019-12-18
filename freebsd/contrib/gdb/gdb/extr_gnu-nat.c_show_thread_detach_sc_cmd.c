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
struct proc {int /*<<< orphan*/  detach_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 struct proc* cur_thread () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 

__attribute__((used)) static void
show_thread_detach_sc_cmd (char *args, int from_tty)
{
  struct proc *thread = cur_thread ();
  check_empty (args, "show thread detach-suspend-count");
  printf_unfiltered ("Thread %s will be left with a suspend count"
		     " of %d when detaching.\n",
		     proc_string (thread),
		     thread->detach_sc);
}