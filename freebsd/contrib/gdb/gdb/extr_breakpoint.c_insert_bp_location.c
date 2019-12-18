#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct value {struct value* next; } ;
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
struct bp_location {int inserted; scalar_t__ loc_type; TYPE_3__* owner; scalar_t__ address; int /*<<< orphan*/  shadow_contents; int /*<<< orphan*/ * section; scalar_t__ duplicate; } ;
struct TYPE_8__ {int enable_p; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ args_for_catchpoint_enable ;
struct TYPE_9__ {scalar_t__ disposition; scalar_t__ type; void* enable_state; int /*<<< orphan*/  number; TYPE_1__* related_breakpoint; struct value* val_chain; int /*<<< orphan*/  exp; int /*<<< orphan*/  watchpoint_frame; int /*<<< orphan*/ * exp_valid_block; } ;
struct TYPE_7__ {scalar_t__ disposition; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DISABLE_UNSETTABLE_BREAK (scalar_t__) ; 
 int /*<<< orphan*/  EX_EVENT_CATCH ; 
 int /*<<< orphan*/  EX_EVENT_THROW ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_LAZY (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ bp_access_watchpoint ; 
 scalar_t__ bp_catch_catch ; 
 scalar_t__ bp_catch_exec ; 
 scalar_t__ bp_catch_fork ; 
 scalar_t__ bp_catch_vfork ; 
 void* bp_disabled ; 
 scalar_t__ bp_loc_hardware_breakpoint ; 
 scalar_t__ bp_loc_hardware_watchpoint ; 
 scalar_t__ bp_loc_software_breakpoint ; 
 scalar_t__ bp_read_watchpoint ; 
 void* bp_shlib_disabled ; 
 int /*<<< orphan*/  breakpoint_enabled (TYPE_3__*) ; 
 int catch_errors (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int catch_exceptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cover_target_enable_exception_callback ; 
 struct frame_info* deprecated_selected_frame ; 
 scalar_t__ disp_del_at_next_stop ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ ep_is_exception_catchpoint (TYPE_3__*) ; 
 struct value* evaluate_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 struct frame_info* frame_find_by_id (int /*<<< orphan*/ ) ; 
 int frame_relative_level (struct frame_info*) ; 
 int hw_access ; 
 int hw_read ; 
 int hw_write ; 
 int /*<<< orphan*/  insert_catchpoint ; 
 scalar_t__ lval_memory ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mark_uninserted ; 
 scalar_t__ overlay_debugging ; 
 int /*<<< orphan*/  overlay_events_enabled ; 
 scalar_t__ overlay_unmapped_address (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ovly_off ; 
 int /*<<< orphan*/  print_address_numeric (scalar_t__,int,struct ui_file*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  remove_breakpoint (struct bp_location*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 scalar_t__ section_is_mapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  section_is_overlay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int target_insert_breakpoint (scalar_t__,int /*<<< orphan*/ ) ; 
 int target_insert_hw_breakpoint (scalar_t__,int /*<<< orphan*/ ) ; 
 int target_insert_watchpoint (scalar_t__,int,int) ; 
 int /*<<< orphan*/  uiout ; 
 struct value* value_mark () ; 
 int /*<<< orphan*/  value_release_to_mark (struct value*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
insert_bp_location (struct bp_location *bpt,
		    struct ui_file *tmp_error_stream,
		    int *disabled_breaks, int *process_warning,
		    int *hw_breakpoint_error)
{
  int val = 0;

  /* Permanent breakpoints cannot be inserted or removed.  Disabled
     breakpoints should not be inserted.  */
  if (!breakpoint_enabled (bpt->owner))
    return 0;

  if (bpt->inserted || bpt->duplicate)
    return 0;

  if (bpt->loc_type == bp_loc_software_breakpoint
      || bpt->loc_type == bp_loc_hardware_breakpoint)
    {
      /* First check to see if we have to handle an overlay.  */
      if (overlay_debugging == ovly_off
	  || bpt->section == NULL
	  || !(section_is_overlay (bpt->section)))
	{
	  /* No overlay handling: just set the breakpoint.  */

	  if (bpt->loc_type == bp_loc_hardware_breakpoint)
	    val = target_insert_hw_breakpoint (bpt->address, 
					       bpt->shadow_contents);
	  else
	    val = target_insert_breakpoint (bpt->address,
					    bpt->shadow_contents);
	}
      else
	{
	  /* This breakpoint is in an overlay section.  
	     Shall we set a breakpoint at the LMA?  */
	  if (!overlay_events_enabled)
	    {
	      /* Yes -- overlay event support is not active, 
		 so we must try to set a breakpoint at the LMA.
		 This will not work for a hardware breakpoint.  */
	      if (bpt->loc_type == bp_loc_hardware_breakpoint)
		warning ("hardware breakpoint %d not supported in overlay!\n",
			 bpt->owner->number);
	      else
		{
		  CORE_ADDR addr = overlay_unmapped_address (bpt->address,
							     bpt->section);
		  /* Set a software (trap) breakpoint at the LMA.  */
		  val = target_insert_breakpoint (addr, bpt->shadow_contents);
		  if (val != 0)
		    fprintf_unfiltered (tmp_error_stream, 
					"Overlay breakpoint %d failed: in ROM?", 
					bpt->owner->number);
		}
	    }
	  /* Shall we set a breakpoint at the VMA? */
	  if (section_is_mapped (bpt->section))
	    {
	      /* Yes.  This overlay section is mapped into memory.  */
	      if (bpt->loc_type == bp_loc_hardware_breakpoint)
		val = target_insert_hw_breakpoint (bpt->address, 
						   bpt->shadow_contents);
	      else
		val = target_insert_breakpoint (bpt->address,
						bpt->shadow_contents);
	    }
	  else
	    {
	      /* No.  This breakpoint will not be inserted.  
		 No error, but do not mark the bp as 'inserted'.  */
	      return 0;
	    }
	}

      if (val)
	{
	  /* Can't set the breakpoint.  */
#if defined (DISABLE_UNSETTABLE_BREAK)
	  if (DISABLE_UNSETTABLE_BREAK (bpt->address))
	    {
	      /* See also: disable_breakpoints_in_shlibs. */
	      val = 0;
	      bpt->owner->enable_state = bp_shlib_disabled;
	      if (!*disabled_breaks)
		{
		  fprintf_unfiltered (tmp_error_stream, 
				      "Cannot insert breakpoint %d.\n", 
				      bpt->owner->number);
		  fprintf_unfiltered (tmp_error_stream, 
				      "Temporarily disabling shared library breakpoints:\n");
		}
	      *disabled_breaks = 1;
	      fprintf_unfiltered (tmp_error_stream,
				  "breakpoint #%d\n", bpt->owner->number);
	    }
	  else
#endif
	    {
#ifdef ONE_PROCESS_WRITETEXT
	      *process_warning = 1;
#endif
	      if (bpt->loc_type == bp_loc_hardware_breakpoint)
		{
		  *hw_breakpoint_error = 1;
		  fprintf_unfiltered (tmp_error_stream, 
				      "Cannot insert hardware breakpoint %d.\n",
				      bpt->owner->number);
		}
	      else
		{
		  fprintf_unfiltered (tmp_error_stream, 
				      "Cannot insert breakpoint %d.\n", 
				      bpt->owner->number);
		  fprintf_filtered (tmp_error_stream, 
				    "Error accessing memory address ");
		  print_address_numeric (bpt->address, 1, tmp_error_stream);
		  fprintf_filtered (tmp_error_stream, ": %s.\n",
				    safe_strerror (val));
		}

	    }
	}
      else
	bpt->inserted = 1;

      return val;
    }

  else if (bpt->loc_type == bp_loc_hardware_watchpoint
	   /* NOTE drow/2003-09-08: This state only exists for removing
	      watchpoints.  It's not clear that it's necessary... */
	   && bpt->owner->disposition != disp_del_at_next_stop)
    {
      /* FIXME drow/2003-09-08: This code sets multiple hardware watchpoints
	 based on the expression.  Ideally this should happen at a higher level,
	 and there should be one bp_location for each computed address we
	 must watch.  As soon as a many-to-one mapping is available I'll
	 convert this.  */

      struct frame_info *saved_frame;
      int saved_level, within_current_scope;
      struct value *mark = value_mark ();
      struct value *v;

      /* Save the current frame and level so we can restore it after
	 evaluating the watchpoint expression on its own frame.  */
      /* FIXME drow/2003-09-09: It would be nice if evaluate_expression
	 took a frame parameter, so that we didn't have to change the
	 selected frame.  */
      saved_frame = deprecated_selected_frame;
      saved_level = frame_relative_level (deprecated_selected_frame);

      /* Determine if the watchpoint is within scope.  */
      if (bpt->owner->exp_valid_block == NULL)
	within_current_scope = 1;
      else
	{
	  struct frame_info *fi;
	  fi = frame_find_by_id (bpt->owner->watchpoint_frame);
	  within_current_scope = (fi != NULL);
	  if (within_current_scope)
	    select_frame (fi);
	}

      if (within_current_scope)
	{
	  /* Evaluate the expression and cut the chain of values
	     produced off from the value chain.

	     Make sure the value returned isn't lazy; we use
	     laziness to determine what memory GDB actually needed
	     in order to compute the value of the expression.  */
	  v = evaluate_expression (bpt->owner->exp);
	  VALUE_CONTENTS (v);
	  value_release_to_mark (mark);

	  bpt->owner->val_chain = v;
	  bpt->inserted = 1;

	  /* Look at each value on the value chain.  */
	  for (; v; v = v->next)
	    {
	      /* If it's a memory location, and GDB actually needed
		 its contents to evaluate the expression, then we
		 must watch it.  */
	      if (VALUE_LVAL (v) == lval_memory
		  && ! VALUE_LAZY (v))
		{
		  struct type *vtype = check_typedef (VALUE_TYPE (v));

		  /* We only watch structs and arrays if user asked
		     for it explicitly, never if they just happen to
		     appear in the middle of some value chain.  */
		  if (v == bpt->owner->val_chain
		      || (TYPE_CODE (vtype) != TYPE_CODE_STRUCT
			  && TYPE_CODE (vtype) != TYPE_CODE_ARRAY))
		    {
		      CORE_ADDR addr;
		      int len, type;

		      addr = VALUE_ADDRESS (v) + VALUE_OFFSET (v);
		      len = TYPE_LENGTH (VALUE_TYPE (v));
		      type = hw_write;
		      if (bpt->owner->type == bp_read_watchpoint)
			type = hw_read;
		      else if (bpt->owner->type == bp_access_watchpoint)
			type = hw_access;

		      val = target_insert_watchpoint (addr, len, type);
		      if (val == -1)
			{
			  /* Don't exit the loop, try to insert
			     every value on the value chain.  That's
			     because we will be removing all the
			     watches below, and removing a
			     watchpoint we didn't insert could have
			     adverse effects.  */
			  bpt->inserted = 0;
			}
		      val = 0;
		    }
		}
	    }
	  /* Failure to insert a watchpoint on any memory value in the
	     value chain brings us here.  */
	  if (!bpt->inserted)
	    {
	      remove_breakpoint (bpt, mark_uninserted);
	      *hw_breakpoint_error = 1;
	      fprintf_unfiltered (tmp_error_stream,
				  "Could not insert hardware watchpoint %d.\n", 
				  bpt->owner->number);
	      val = -1;
	    }               
	}
      else
	{
	  printf_filtered ("Hardware watchpoint %d deleted ", bpt->owner->number);
	  printf_filtered ("because the program has left the block \n");
	  printf_filtered ("in which its expression is valid.\n");
	  if (bpt->owner->related_breakpoint)
	    bpt->owner->related_breakpoint->disposition = disp_del_at_next_stop;
	  bpt->owner->disposition = disp_del_at_next_stop;
	}

      /* Restore the frame and level.  */
      if (saved_frame != deprecated_selected_frame
	  || saved_level != frame_relative_level (deprecated_selected_frame))
	select_frame (saved_frame);

      return val;
    }

  else if (ep_is_exception_catchpoint (bpt->owner))
    {
      /* FIXME drow/2003-09-09: This code sets both a catchpoint and a
	 breakpoint.  Once again, it would be better if this was represented
	 as two bp_locations.  */

      /* If we get here, we must have a callback mechanism for exception
	 events -- with g++ style embedded label support, we insert
	 ordinary breakpoints and not catchpoints. */
      val = target_insert_breakpoint (bpt->address, bpt->shadow_contents);
      if (val)
	{
	  /* Couldn't set breakpoint for some reason */
	  fprintf_unfiltered (tmp_error_stream, 
			      "Cannot insert catchpoint %d; disabling it.\n",
			      bpt->owner->number);
	  fprintf_filtered (tmp_error_stream, 
			    "Error accessing memory address ");
	  print_address_numeric (bpt->address, 1, tmp_error_stream);
	  fprintf_filtered (tmp_error_stream, ": %s.\n",
			    safe_strerror (val));
	  bpt->owner->enable_state = bp_disabled;
	}
      else
	{
	  /* Bp set, now make sure callbacks are enabled */
	  /* Format possible error msg */
	  char *message = xstrprintf ("Error inserting catchpoint %d:\n",
				      bpt->owner->number);
	  struct cleanup *cleanups = make_cleanup (xfree, message);
	  int val;
	  args_for_catchpoint_enable args;
	  args.kind = bpt->owner->type == bp_catch_catch ? 
	    EX_EVENT_CATCH : EX_EVENT_THROW;
	  args.enable_p = 1;
	  val = catch_errors (cover_target_enable_exception_callback,
			      &args, message, RETURN_MASK_ALL);
	  do_cleanups (cleanups);
	  if (val != 0 && val != -1)
	    bpt->inserted = 1;

	  /* Check if something went wrong; val == 0 can be ignored */
	  if (val == -1)
	    {
	      /* something went wrong */
	      fprintf_unfiltered (tmp_error_stream, 
				  "Cannot insert catchpoint %d; disabling it.\n",
				  bpt->owner->number);
	      bpt->owner->enable_state = bp_disabled;
	    }
	}

      return val;
    }

  else if (bpt->owner->type == bp_catch_fork
	   || bpt->owner->type == bp_catch_vfork
	   || bpt->owner->type == bp_catch_exec)
    {
      char *prefix = xstrprintf ("warning: inserting catchpoint %d: ",
				 bpt->owner->number);
      struct cleanup *cleanups = make_cleanup (xfree, prefix);
      val = catch_exceptions (uiout, insert_catchpoint, bpt->owner, prefix,
			      RETURN_MASK_ERROR);
      do_cleanups (cleanups);
      if (val < 0)
	bpt->owner->enable_state = bp_disabled;
      else
	bpt->inserted = 1;

      /* We've already printed an error message if there was a problem
	 inserting this catchpoint, and we've disabled the catchpoint,
	 so just return success.  */
      return 0;
    }

  return 0;
}