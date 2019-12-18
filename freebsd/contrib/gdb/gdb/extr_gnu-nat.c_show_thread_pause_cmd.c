#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc {int pause_sc; TYPE_1__* inf; } ;
struct TYPE_2__ {scalar_t__ pause_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 struct proc* cur_thread () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 

__attribute__((used)) static void
show_thread_pause_cmd (char *args, int from_tty)
{
  struct proc *thread = cur_thread ();
  int sc = thread->pause_sc;
  check_empty (args, "show task pause");
  printf_unfiltered ("Thread %s %s suspended while gdb has control%s.\n",
		     proc_string (thread),
		     sc ? "is" : "isn't",
		     !sc && thread->inf->pause_sc ? " (but the task is)" : "");
}