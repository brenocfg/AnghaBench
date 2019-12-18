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
struct value {int dummy; } ;
struct frame_info {int dummy; } ;
struct breakpoint {void* disposition; TYPE_1__* related_breakpoint; int /*<<< orphan*/  number; struct value* val; int /*<<< orphan*/  exp; int /*<<< orphan*/  watchpoint_frame; int /*<<< orphan*/ * exp_valid_block; } ;
typedef  TYPE_2__* bpstat ;
struct TYPE_4__ {struct breakpoint* breakpoint_at; struct value* old_val; } ;
struct TYPE_3__ {void* disposition; } ;

/* Variables and functions */
 int WP_DELETED ; 
 int WP_VALUE_CHANGED ; 
 int WP_VALUE_NOT_CHANGED ; 
 int /*<<< orphan*/  current_gdbarch ; 
 void* disp_del_at_next_stop ; 
 struct value* evaluate_expression (int /*<<< orphan*/ ) ; 
 struct frame_info* frame_find_by_id (int /*<<< orphan*/ ) ; 
 scalar_t__ gdbarch_in_function_epilogue_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ui_out_is_mi_like_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  value_equal (struct value*,struct value*) ; 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_mark () ; 

__attribute__((used)) static int
watchpoint_check (void *p)
{
  bpstat bs = (bpstat) p;
  struct breakpoint *b;
  struct frame_info *fr;
  int within_current_scope;

  b = bs->breakpoint_at;

  if (b->exp_valid_block == NULL)
    within_current_scope = 1;
  else
    {
      /* There is no current frame at this moment.  If we're going to have
         any chance of handling watchpoints on local variables, we'll need
         the frame chain (so we can determine if we're in scope).  */
      reinit_frame_cache ();
      fr = frame_find_by_id (b->watchpoint_frame);
      within_current_scope = (fr != NULL);
      /* in_function_epilogue_p() returns a non-zero value if we're still
	 in the function but the stack frame has already been invalidated.
	 Since we can't rely on the values of local variables after the
	 stack has been destroyed, we are treating the watchpoint in that
	 state as `not changed' without further checking.
	 
	 vinschen/2003-09-04: The former implementation left out the case
	 that the watchpoint frame couldn't be found by frame_find_by_id()
	 because the current PC is currently in an epilogue.  Calling
	 gdbarch_in_function_epilogue_p() also when fr == NULL fixes that. */
      if ((!within_current_scope || fr == get_current_frame ())
          && gdbarch_in_function_epilogue_p (current_gdbarch, read_pc ()))
	return WP_VALUE_NOT_CHANGED;
      if (fr && within_current_scope)
	/* If we end up stopping, the current frame will get selected
	   in normal_stop.  So this call to select_frame won't affect
	   the user.  */
	select_frame (fr);
    }

  if (within_current_scope)
    {
      /* We use value_{,free_to_}mark because it could be a
         *long* time before we return to the command level and
         call free_all_values.  We can't call free_all_values because
         we might be in the middle of evaluating a function call.  */

      struct value *mark = value_mark ();
      struct value *new_val = evaluate_expression (bs->breakpoint_at->exp);
      if (!value_equal (b->val, new_val))
	{
	  release_value (new_val);
	  value_free_to_mark (mark);
	  bs->old_val = b->val;
	  b->val = new_val;
	  /* We will stop here */
	  return WP_VALUE_CHANGED;
	}
      else
	{
	  /* Nothing changed, don't do anything.  */
	  value_free_to_mark (mark);
	  /* We won't stop here */
	  return WP_VALUE_NOT_CHANGED;
	}
    }
  else
    {
      /* This seems like the only logical thing to do because
         if we temporarily ignored the watchpoint, then when
         we reenter the block in which it is valid it contains
         garbage (in the case of a function, it may have two
         garbage values, one before and one after the prologue).
         So we can't even detect the first assignment to it and
         watch after that (since the garbage may or may not equal
         the first value assigned).  */
      /* We print all the stop information in print_it_typical(), but
	 in this case, by the time we call print_it_typical() this bp
	 will be deleted already. So we have no choice but print the
	 information here. */
      if (ui_out_is_mi_like_p (uiout))
	ui_out_field_string (uiout, "reason", "watchpoint-scope");
      ui_out_text (uiout, "\nWatchpoint ");
      ui_out_field_int (uiout, "wpnum", bs->breakpoint_at->number);
      ui_out_text (uiout, " deleted because the program has left the block in\n\
which its expression is valid.\n");     

      if (b->related_breakpoint)
	b->related_breakpoint->disposition = disp_del_at_next_stop;
      b->disposition = disp_del_at_next_stop;

      return WP_DELETED;
    }
}