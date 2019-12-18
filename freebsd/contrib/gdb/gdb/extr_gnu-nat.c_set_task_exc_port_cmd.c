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
struct inf {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  steal_exc_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_task_exc_port_cmd (char *args, int from_tty)
{
  struct inf *inf = cur_inf ();
  if (!args)
    error ("No argument to \"set task exception-port\" command.");
  steal_exc_port (inf->task, parse_and_eval_address (args));
}