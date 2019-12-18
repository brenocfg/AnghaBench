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
struct frame_info {int dummy; } ;
struct TYPE_2__ {int integer; } ;
struct continuation_arg {TYPE_1__ data; struct continuation_arg* next; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  STEP_OVER_ALL ; 
 int /*<<< orphan*/  STEP_OVER_NONE ; 
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  add_intermediate_continuation (int /*<<< orphan*/ ,struct continuation_arg*) ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  find_pc_line_pc_range (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ find_pc_partial_function (int /*<<< orphan*/ ,char**,int*,int*) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  step_1_continuation ; 
 int /*<<< orphan*/  step_frame_id ; 
 int step_multi ; 
 int /*<<< orphan*/  step_over_calls ; 
 int step_range_end ; 
 int step_range_start ; 
 int /*<<< orphan*/  step_sp ; 
 scalar_t__ step_stop_if_no_debug ; 
 int /*<<< orphan*/  stop_pc ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void 
step_once (int skip_subroutines, int single_inst, int count)
{ 
  struct continuation_arg *arg1; 
  struct continuation_arg *arg2;
  struct continuation_arg *arg3; 
  struct frame_info *frame;

  if (count > 0)
    {
      clear_proceed_status ();

      frame = get_current_frame ();
      if (!frame)		/* Avoid coredump here.  Why tho? */
	error ("No current frame");
      step_frame_id = get_frame_id (frame);
      step_sp = read_sp ();

      if (!single_inst)
	{
	  find_pc_line_pc_range (stop_pc, &step_range_start, &step_range_end);

	  /* If we have no line info, switch to stepi mode.  */
	  if (step_range_end == 0 && step_stop_if_no_debug)
	    {
	      step_range_start = step_range_end = 1;
	    }
	  else if (step_range_end == 0)
	    {
	      char *name;
	      if (find_pc_partial_function (stop_pc, &name, &step_range_start,
					    &step_range_end) == 0)
		error ("Cannot find bounds of current function");

	      target_terminal_ours ();
	      printf_filtered ("\
Single stepping until exit from function %s, \n\
which has no line number information.\n", name);
	    }
	}
      else
	{
	  /* Say we are stepping, but stop after one insn whatever it does.  */
	  step_range_start = step_range_end = 1;
	  if (!skip_subroutines)
	    /* It is stepi.
	       Don't step over function calls, not even to functions lacking
	       line numbers.  */
	    step_over_calls = STEP_OVER_NONE;
	}

      if (skip_subroutines)
	step_over_calls = STEP_OVER_ALL;

      step_multi = (count > 1);
      arg1 =
	(struct continuation_arg *) xmalloc (sizeof (struct continuation_arg));
      arg2 =
	(struct continuation_arg *) xmalloc (sizeof (struct continuation_arg));
      arg3 =
	(struct continuation_arg *) xmalloc (sizeof (struct continuation_arg));
      arg1->next = arg2;
      arg1->data.integer = skip_subroutines;
      arg2->next = arg3;
      arg2->data.integer = single_inst;
      arg3->next = NULL;
      arg3->data.integer = count;
      add_intermediate_continuation (step_1_continuation, arg1);
      proceed ((CORE_ADDR) -1, TARGET_SIGNAL_DEFAULT, 1);
    }
}