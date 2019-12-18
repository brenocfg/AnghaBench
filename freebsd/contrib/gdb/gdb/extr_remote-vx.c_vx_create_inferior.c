#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  taskStart ;
typedef  int /*<<< orphan*/  passArgs ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_6__ {scalar_t__ arg_array_len; int /*<<< orphan*/ * arg_array_val; } ;
typedef  TYPE_1__ arg_array ;
struct TYPE_7__ {int status; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ TASK_START ;

/* Variables and functions */
 int /*<<< orphan*/  NO_STOP_QUIETLY ; 
 int /*<<< orphan*/  PROCESS_START ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  STOP_QUIETLY ; 
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  parse_args (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proceed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_soon ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 
 int /*<<< orphan*/  target_terminal_init () ; 
 int /*<<< orphan*/  vx_run_ops ; 
 int /*<<< orphan*/  vx_running ; 
 int /*<<< orphan*/  wait_for_inferior () ; 
 int /*<<< orphan*/  xdr_TASK_START ; 
 int /*<<< orphan*/  xdr_arg_array ; 

__attribute__((used)) static void
vx_create_inferior (char *exec_file, char *args, char **env)
{
  enum clnt_stat status;
  arg_array passArgs;
  TASK_START taskStart;

  memset ((char *) &passArgs, '\0', sizeof (passArgs));
  memset ((char *) &taskStart, '\0', sizeof (taskStart));

  /* parse arguments, put them in passArgs */

  parse_args (args, &passArgs);

  if (passArgs.arg_array_len == 0)
    error ("You must specify a function name to run, and arguments if any");

  status = net_clnt_call (PROCESS_START, xdr_arg_array, &passArgs,
			  xdr_TASK_START, &taskStart);

  if ((status != RPC_SUCCESS) || (taskStart.status == -1))
    error ("Can't create process on remote target machine");

  /* Save the name of the running function */
  vx_running = savestring (passArgs.arg_array_val[0],
			   strlen (passArgs.arg_array_val[0]));

  push_target (&vx_run_ops);
  inferior_ptid = pid_to_ptid (taskStart.pid);

  /* We will get a trace trap after one instruction.
     Insert breakpoints and continue.  */

  init_wait_for_inferior ();

  /* Set up the "saved terminal modes" of the inferior
     based on what modes we are starting it with.  */
  target_terminal_init ();

  /* Install inferior's terminal modes.  */
  target_terminal_inferior ();

  stop_soon = STOP_QUIETLY;
  wait_for_inferior ();		/* Get the task spawn event */
  stop_soon = NO_STOP_QUIETLY;

  /* insert_step_breakpoint ();  FIXME, do we need this?  */
  proceed (-1, TARGET_SIGNAL_DEFAULT, 0);
}