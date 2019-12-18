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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {int /*<<< orphan*/  pc; } ;
struct symtab {int dummy; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {struct cleanup* pointer; } ;
struct continuation_arg {TYPE_1__ data; int /*<<< orphan*/ * next; } ;
struct cleanup {int dummy; } ;
struct breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  add_continuation (int /*<<< orphan*/ ,struct continuation_arg*) ; 
 int /*<<< orphan*/  bp_until ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 struct symtabs_and_lines decode_line_1 (char**,int,struct symtab*,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_breakpoint_line ; 
 struct symtab* default_breakpoint_symtab ; 
 scalar_t__ default_breakpoint_valid ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ event_loop_p ; 
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 struct cleanup* make_cleanup_delete_breakpoint (struct breakpoint*) ; 
 struct cleanup* make_exec_cleanup_delete_breakpoint (struct breakpoint*) ; 
 int /*<<< orphan*/  null_frame_id ; 
 int /*<<< orphan*/  proceed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_sal_pc (struct symtab_and_line*) ; 
 struct breakpoint* set_momentary_breakpoint (struct symtab_and_line,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  until_break_command_continuation ; 
 int /*<<< orphan*/  xfree (struct symtab_and_line*) ; 
 scalar_t__ xmalloc (int) ; 

void
until_break_command (char *arg, int from_tty, int anywhere)
{
  struct symtabs_and_lines sals;
  struct symtab_and_line sal;
  struct frame_info *prev_frame = get_prev_frame (deprecated_selected_frame);
  struct breakpoint *breakpoint;
  struct cleanup *old_chain;
  struct continuation_arg *arg1;


  clear_proceed_status ();

  /* Set a breakpoint where the user wants it and at return from
     this function */

  if (default_breakpoint_valid)
    sals = decode_line_1 (&arg, 1, default_breakpoint_symtab,
			  default_breakpoint_line, (char ***) NULL, NULL);
  else
    sals = decode_line_1 (&arg, 1, (struct symtab *) NULL, 
			  0, (char ***) NULL, NULL);

  if (sals.nelts != 1)
    error ("Couldn't get information on specified line.");

  sal = sals.sals[0];
  xfree (sals.sals);	/* malloc'd, so freed */

  if (*arg)
    error ("Junk at end of arguments.");

  resolve_sal_pc (&sal);

  if (anywhere)
    /* If the user told us to continue until a specified location,
       we don't specify a frame at which we need to stop.  */
    breakpoint = set_momentary_breakpoint (sal, null_frame_id, bp_until);
  else
    /* Otherwise, specify the current frame, because we want to stop only
       at the very same frame.  */
    breakpoint = set_momentary_breakpoint (sal,
					   get_frame_id (deprecated_selected_frame),
					   bp_until);

  if (!event_loop_p || !target_can_async_p ())
    old_chain = make_cleanup_delete_breakpoint (breakpoint);
  else
    old_chain = make_exec_cleanup_delete_breakpoint (breakpoint);

  /* If we are running asynchronously, and the target supports async
     execution, we are not waiting for the target to stop, in the call
     tp proceed, below. This means that we cannot delete the
     brekpoints until the target has actually stopped. The only place
     where we get a chance to do that is in fetch_inferior_event, so
     we must set things up for that. */

  if (event_loop_p && target_can_async_p ())
    {
      /* In this case the arg for the continuation is just the point
         in the exec_cleanups chain from where to start doing
         cleanups, because all the continuation does is the cleanups in
         the exec_cleanup_chain. */
      arg1 =
	(struct continuation_arg *) xmalloc (sizeof (struct continuation_arg));
      arg1->next         = NULL;
      arg1->data.pointer = old_chain;

      add_continuation (until_break_command_continuation, arg1);
    }

  /* Keep within the current frame, or in frames called by the current
     one.  */
  if (prev_frame)
    {
      sal = find_pc_line (get_frame_pc (prev_frame), 0);
      sal.pc = get_frame_pc (prev_frame);
      breakpoint = set_momentary_breakpoint (sal, get_frame_id (prev_frame),
					     bp_until);
      if (!event_loop_p || !target_can_async_p ())
	make_cleanup_delete_breakpoint (breakpoint);
      else
	make_exec_cleanup_delete_breakpoint (breakpoint);
    }

  proceed (-1, TARGET_SIGNAL_DEFAULT, 0);
  /* Do the cleanups now, anly if we are not running asynchronously,
     of if we are, but the target is still synchronous. */
  if (!event_loop_p || !target_can_async_p ())
    do_cleanups (old_chain);
}