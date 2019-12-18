#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct cleanup {int dummy; } ;
typedef  enum print_stop_action { ____Placeholder_print_stop_action } print_stop_action ;
typedef  TYPE_2__* bpstat ;
struct TYPE_7__ {int type; int /*<<< orphan*/ * val; int /*<<< orphan*/  number; int /*<<< orphan*/  exec_pathname; int /*<<< orphan*/  forked_inferior_pid; int /*<<< orphan*/  triggered_dll_pathname; TYPE_1__* loc; } ;
struct TYPE_6__ {TYPE_4__* breakpoint_at; int /*<<< orphan*/ * old_val; } ;
struct TYPE_5__ {int /*<<< orphan*/  address; int /*<<< orphan*/  requested_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_EXCEPTION_CATCH_FILE ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_CATCH_LINE ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_CATCH_PC ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_KIND ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_THROW_FILE ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_THROW_LINE ; 
 int /*<<< orphan*/  CURRENT_EXCEPTION_THROW_PC ; 
 int /*<<< orphan*/  EX_EVENT_CATCH ; 
 int /*<<< orphan*/  EX_EVENT_THROW ; 
 int PRINT_NOTHING ; 
 int PRINT_SRC_AND_LOC ; 
 int PRINT_SRC_ONLY ; 
 int PRINT_UNKNOWN ; 
 int /*<<< orphan*/  Val_pretty_default ; 
 int /*<<< orphan*/  annotate_breakpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_catchpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_watchpoint (int /*<<< orphan*/ ) ; 
#define  bp_access_watchpoint 152 
#define  bp_breakpoint 151 
#define  bp_call_dummy 150 
#define  bp_catch_catch 149 
#define  bp_catch_exec 148 
#define  bp_catch_fork 147 
#define  bp_catch_load 146 
#define  bp_catch_throw 145 
#define  bp_catch_unload 144 
#define  bp_catch_vfork 143 
#define  bp_finish 142 
#define  bp_hardware_breakpoint 141 
#define  bp_hardware_watchpoint 140 
#define  bp_longjmp 139 
#define  bp_longjmp_resume 138 
#define  bp_none 137 
#define  bp_overlay_event 136 
#define  bp_read_watchpoint 135 
#define  bp_shlib_event 134 
#define  bp_step_resume 133 
#define  bp_thread_event 132 
#define  bp_through_sigtramp 131 
#define  bp_until 130 
#define  bp_watchpoint 129 
#define  bp_watchpoint_scope 128 
 int /*<<< orphan*/  breakpoint_adjustment_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_exception_event ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_out_stream_delete (struct ui_stream*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mention (TYPE_4__*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ui_out_is_mi_like_p (int /*<<< orphan*/ ) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum print_stop_action
print_it_typical (bpstat bs)
{
  struct cleanup *old_chain, *ui_out_chain;
  struct ui_stream *stb;
  stb = ui_out_stream_new (uiout);
  old_chain = make_cleanup_ui_out_stream_delete (stb);
  /* bs->breakpoint_at can be NULL if it was a momentary breakpoint
     which has since been deleted.  */
  if (bs->breakpoint_at == NULL)
    return PRINT_UNKNOWN;

  switch (bs->breakpoint_at->type)
    {
    case bp_breakpoint:
    case bp_hardware_breakpoint:
      if (bs->breakpoint_at->loc->address != bs->breakpoint_at->loc->requested_address)
	breakpoint_adjustment_warning (bs->breakpoint_at->loc->requested_address,
	                               bs->breakpoint_at->loc->address,
				       bs->breakpoint_at->number, 1);
      annotate_breakpoint (bs->breakpoint_at->number);
      ui_out_text (uiout, "\nBreakpoint ");
      if (ui_out_is_mi_like_p (uiout))
	ui_out_field_string (uiout, "reason", "breakpoint-hit");
      ui_out_field_int (uiout, "bkptno", bs->breakpoint_at->number);
      ui_out_text (uiout, ", ");
      return PRINT_SRC_AND_LOC;
      break;

    case bp_shlib_event:
      /* Did we stop because the user set the stop_on_solib_events
	 variable?  (If so, we report this as a generic, "Stopped due
	 to shlib event" message.) */
      printf_filtered ("Stopped due to shared library event\n");
      return PRINT_NOTHING;
      break;

    case bp_thread_event:
      /* Not sure how we will get here. 
	 GDB should not stop for these breakpoints.  */
      printf_filtered ("Thread Event Breakpoint: gdb should not stop!\n");
      return PRINT_NOTHING;
      break;

    case bp_overlay_event:
      /* By analogy with the thread event, GDB should not stop for these. */
      printf_filtered ("Overlay Event Breakpoint: gdb should not stop!\n");
      return PRINT_NOTHING;
      break;

    case bp_catch_load:
      annotate_catchpoint (bs->breakpoint_at->number);
      printf_filtered ("\nCatchpoint %d (", bs->breakpoint_at->number);
      printf_filtered ("loaded");
      printf_filtered (" %s), ", bs->breakpoint_at->triggered_dll_pathname);
      return PRINT_SRC_AND_LOC;
      break;

    case bp_catch_unload:
      annotate_catchpoint (bs->breakpoint_at->number);
      printf_filtered ("\nCatchpoint %d (", bs->breakpoint_at->number);
      printf_filtered ("unloaded");
      printf_filtered (" %s), ", bs->breakpoint_at->triggered_dll_pathname);
      return PRINT_SRC_AND_LOC;
      break;

    case bp_catch_fork:
      annotate_catchpoint (bs->breakpoint_at->number);
      printf_filtered ("\nCatchpoint %d (", bs->breakpoint_at->number);
      printf_filtered ("forked");
      printf_filtered (" process %d), ", 
		       bs->breakpoint_at->forked_inferior_pid);
      return PRINT_SRC_AND_LOC;
      break;

    case bp_catch_vfork:
      annotate_catchpoint (bs->breakpoint_at->number);
      printf_filtered ("\nCatchpoint %d (", bs->breakpoint_at->number);
      printf_filtered ("vforked");
      printf_filtered (" process %d), ", 
		       bs->breakpoint_at->forked_inferior_pid);
      return PRINT_SRC_AND_LOC;
      break;

    case bp_catch_exec:
      annotate_catchpoint (bs->breakpoint_at->number);
      printf_filtered ("\nCatchpoint %d (exec'd %s), ",
		       bs->breakpoint_at->number,
		       bs->breakpoint_at->exec_pathname);
      return PRINT_SRC_AND_LOC;
      break;

    case bp_catch_catch:
      if (current_exception_event && 
	  (CURRENT_EXCEPTION_KIND == EX_EVENT_CATCH))
	{
	  annotate_catchpoint (bs->breakpoint_at->number);
	  printf_filtered ("\nCatchpoint %d (exception caught), ", 
			   bs->breakpoint_at->number);
	  printf_filtered ("throw location ");
	  if (CURRENT_EXCEPTION_THROW_PC && CURRENT_EXCEPTION_THROW_LINE)
	    printf_filtered ("%s:%d",
			     CURRENT_EXCEPTION_THROW_FILE,
			     CURRENT_EXCEPTION_THROW_LINE);
	  else
	    printf_filtered ("unknown");

	  printf_filtered (", catch location ");
	  if (CURRENT_EXCEPTION_CATCH_PC && CURRENT_EXCEPTION_CATCH_LINE)
	    printf_filtered ("%s:%d",
			     CURRENT_EXCEPTION_CATCH_FILE,
			     CURRENT_EXCEPTION_CATCH_LINE);
	  else
	    printf_filtered ("unknown");

	  printf_filtered ("\n");
	  /* don't bother to print location frame info */
	  return PRINT_SRC_ONLY;
	}
      else
	{
	  /* really throw, some other bpstat will handle it */
	  return PRINT_UNKNOWN;	
	}
      break;

    case bp_catch_throw:
      if (current_exception_event && 
	  (CURRENT_EXCEPTION_KIND == EX_EVENT_THROW))
	{
	  annotate_catchpoint (bs->breakpoint_at->number);
	  printf_filtered ("\nCatchpoint %d (exception thrown), ",
			   bs->breakpoint_at->number);
	  printf_filtered ("throw location ");
	  if (CURRENT_EXCEPTION_THROW_PC && CURRENT_EXCEPTION_THROW_LINE)
	    printf_filtered ("%s:%d",
			     CURRENT_EXCEPTION_THROW_FILE,
			     CURRENT_EXCEPTION_THROW_LINE);
	  else
	    printf_filtered ("unknown");

	  printf_filtered (", catch location ");
	  if (CURRENT_EXCEPTION_CATCH_PC && CURRENT_EXCEPTION_CATCH_LINE)
	    printf_filtered ("%s:%d",
			     CURRENT_EXCEPTION_CATCH_FILE,
			     CURRENT_EXCEPTION_CATCH_LINE);
	  else
	    printf_filtered ("unknown");

	  printf_filtered ("\n");
	  /* don't bother to print location frame info */
	  return PRINT_SRC_ONLY; 
	}
      else
	{
	  /* really catch, some other bpstat will handle it */
	  return PRINT_UNKNOWN;	
	}
      break;

    case bp_watchpoint:
    case bp_hardware_watchpoint:
      if (bs->old_val != NULL)
	{
	  annotate_watchpoint (bs->breakpoint_at->number);
	  if (ui_out_is_mi_like_p (uiout))
	    ui_out_field_string (uiout, "reason", "watchpoint-trigger");
	  mention (bs->breakpoint_at);
	  ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "value");
	  ui_out_text (uiout, "\nOld value = ");
	  value_print (bs->old_val, stb->stream, 0, Val_pretty_default);
	  ui_out_field_stream (uiout, "old", stb);
	  ui_out_text (uiout, "\nNew value = ");
	  value_print (bs->breakpoint_at->val, stb->stream, 0, Val_pretty_default);
	  ui_out_field_stream (uiout, "new", stb);
	  do_cleanups (ui_out_chain);
	  ui_out_text (uiout, "\n");
	  value_free (bs->old_val);
	  bs->old_val = NULL;
	}
      /* More than one watchpoint may have been triggered.  */
      return PRINT_UNKNOWN;
      break;

    case bp_read_watchpoint:
      if (ui_out_is_mi_like_p (uiout))
	ui_out_field_string (uiout, "reason", "read-watchpoint-trigger");
      mention (bs->breakpoint_at);
      ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "value");
      ui_out_text (uiout, "\nValue = ");
      value_print (bs->breakpoint_at->val, stb->stream, 0, Val_pretty_default);
      ui_out_field_stream (uiout, "value", stb);
      do_cleanups (ui_out_chain);
      ui_out_text (uiout, "\n");
      return PRINT_UNKNOWN;
      break;

    case bp_access_watchpoint:
      if (bs->old_val != NULL)     
	{
	  annotate_watchpoint (bs->breakpoint_at->number);
	  if (ui_out_is_mi_like_p (uiout))
	    ui_out_field_string (uiout, "reason", "access-watchpoint-trigger");
	  mention (bs->breakpoint_at);
	  ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "value");
	  ui_out_text (uiout, "\nOld value = ");
	  value_print (bs->old_val, stb->stream, 0, Val_pretty_default);
	  ui_out_field_stream (uiout, "old", stb);
	  value_free (bs->old_val);
	  bs->old_val = NULL;
	  ui_out_text (uiout, "\nNew value = ");
	}
      else 
	{
	  mention (bs->breakpoint_at);
	  if (ui_out_is_mi_like_p (uiout))
	    ui_out_field_string (uiout, "reason", "access-watchpoint-trigger");
	  ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "value");
	  ui_out_text (uiout, "\nValue = ");
	}
      value_print (bs->breakpoint_at->val, stb->stream, 0,Val_pretty_default);
      ui_out_field_stream (uiout, "new", stb);
      do_cleanups (ui_out_chain);
      ui_out_text (uiout, "\n");
      return PRINT_UNKNOWN;
      break;

    /* Fall through, we don't deal with these types of breakpoints
       here. */

    case bp_finish:
      if (ui_out_is_mi_like_p (uiout))
	ui_out_field_string (uiout, "reason", "function-finished");
      return PRINT_UNKNOWN;
      break;

    case bp_until:
      if (ui_out_is_mi_like_p (uiout))
	ui_out_field_string (uiout, "reason", "location-reached");
      return PRINT_UNKNOWN;
      break;

    case bp_none:
    case bp_longjmp:
    case bp_longjmp_resume:
    case bp_step_resume:
    case bp_through_sigtramp:
    case bp_watchpoint_scope:
    case bp_call_dummy:
    default:
      return PRINT_UNKNOWN;
    }
}