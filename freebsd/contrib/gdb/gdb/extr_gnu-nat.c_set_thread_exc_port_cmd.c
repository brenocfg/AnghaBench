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
struct proc {int dummy; } ;

/* Variables and functions */
 struct proc* cur_thread () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  steal_exc_port (struct proc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_thread_exc_port_cmd (char *args, int from_tty)
{
  struct proc *thread = cur_thread ();
  if (!args)
    error ("No argument to \"set thread exception-port\" command.");
  steal_exc_port (thread, parse_and_eval_address (args));
}