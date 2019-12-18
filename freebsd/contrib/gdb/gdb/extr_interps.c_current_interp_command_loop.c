#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; TYPE_1__* procs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* command_loop_proc ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cli_command_loop () ; 
 int /*<<< orphan*/  command_loop () ; 
 int /*<<< orphan*/  command_loop_hook () ; 
 TYPE_2__* current_interpreter ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
current_interp_command_loop (void)
{
  /* Somewhat messy.  For the moment prop up all the old ways of
     selecting the command loop.  `command_loop_hook' should be
     deprecated.  */
  if (command_loop_hook != NULL)
    command_loop_hook ();
  else if (current_interpreter != NULL
	   && current_interpreter->procs->command_loop_proc != NULL)
    current_interpreter->procs->command_loop_proc (current_interpreter->data);
  else if (event_loop_p)
    cli_command_loop ();
  else
    command_loop ();
}