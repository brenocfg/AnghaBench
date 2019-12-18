#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _Unwind_Exception {int /*<<< orphan*/  private_2; scalar_t__ private_1; int /*<<< orphan*/  exception_class; } ;
struct _Unwind_Context {int dummy; } ;
typedef  scalar_t__ _Unwind_Reason_Code ;
struct TYPE_4__ {scalar_t__ (* personality ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*) ;} ;
typedef  TYPE_1__ _Unwind_FrameState ;

/* Variables and functions */
 int /*<<< orphan*/  _UA_SEARCH_PHASE ; 
 scalar_t__ _URC_CONTINUE_UNWIND ; 
 scalar_t__ _URC_END_OF_STACK ; 
 scalar_t__ _URC_FATAL_PHASE1_ERROR ; 
 scalar_t__ _URC_HANDLER_FOUND ; 
 scalar_t__ _URC_INSTALL_CONTEXT ; 
 scalar_t__ _URC_NO_REASON ; 
 scalar_t__ _Unwind_RaiseException_Phase2 (struct _Unwind_Exception*,struct _Unwind_Context*) ; 
 scalar_t__ stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*) ; 
 scalar_t__ uw_frame_state_for (struct _Unwind_Context*,TYPE_1__*) ; 
 int /*<<< orphan*/  uw_identify_context (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_init_context (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_install_context (struct _Unwind_Context*,struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_update_context (struct _Unwind_Context*,TYPE_1__*) ; 

_Unwind_Reason_Code
_Unwind_RaiseException(struct _Unwind_Exception *exc)
{
  struct _Unwind_Context this_context, cur_context;
  _Unwind_Reason_Code code;

  /* Set up this_context to describe the current stack frame.  */
  uw_init_context (&this_context);
  cur_context = this_context;

  /* Phase 1: Search.  Unwind the stack, calling the personality routine
     with the _UA_SEARCH_PHASE flag set.  Do not modify the stack yet.  */
  while (1)
    {
      _Unwind_FrameState fs;

      /* Set up fs to describe the FDE for the caller of cur_context.  The
	 first time through the loop, that means __cxa_throw.  */
      code = uw_frame_state_for (&cur_context, &fs);

      if (code == _URC_END_OF_STACK)
	/* Hit end of stack with no handler found.  */
	return _URC_END_OF_STACK;

      if (code != _URC_NO_REASON)
	/* Some error encountered.  Ususally the unwinder doesn't
	   diagnose these and merely crashes.  */
	return _URC_FATAL_PHASE1_ERROR;

      /* Unwind successful.  Run the personality routine, if any.  */
      if (fs.personality)
	{
	  code = (*fs.personality) (1, _UA_SEARCH_PHASE, exc->exception_class,
				    exc, &cur_context);
	  if (code == _URC_HANDLER_FOUND)
	    break;
	  else if (code != _URC_CONTINUE_UNWIND)
	    return _URC_FATAL_PHASE1_ERROR;
	}

      /* Update cur_context to describe the same frame as fs.  */
      uw_update_context (&cur_context, &fs);
    }

  /* Indicate to _Unwind_Resume and associated subroutines that this
     is not a forced unwind.  Further, note where we found a handler.  */
  exc->private_1 = 0;
  exc->private_2 = uw_identify_context (&cur_context);

  cur_context = this_context;
  code = _Unwind_RaiseException_Phase2 (exc, &cur_context);
  if (code != _URC_INSTALL_CONTEXT)
    return code;

  uw_install_context (&this_context, &cur_context);
}