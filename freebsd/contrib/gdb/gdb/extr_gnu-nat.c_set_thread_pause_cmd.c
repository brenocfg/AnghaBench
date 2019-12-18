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
 struct proc* cur_thread () ; 
 int /*<<< orphan*/  inf_suspend (TYPE_1__*) ; 
 int parse_bool_arg (char*,char*) ; 

__attribute__((used)) static void
set_thread_pause_cmd (char *args, int from_tty)
{
  struct proc *thread = cur_thread ();
  int old_sc = thread->pause_sc;
  thread->pause_sc = parse_bool_arg (args, "set thread pause");
  if (old_sc == 0 && thread->pause_sc != 0 && thread->inf->pause_sc == 0)
    /* If the task is currently unsuspended, immediately suspend it,
       otherwise wait until the next time it gets control.  */
    inf_suspend (thread->inf);
}