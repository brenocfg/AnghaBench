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
struct _Unwind_Exception {int /*<<< orphan*/  exception_class; scalar_t__ private_2; scalar_t__ private_1; } ;
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  (* _Unwind_Stop_Fn ) (int,int,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*,void*) ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;
typedef  scalar_t__ _Unwind_Ptr ;
struct TYPE_4__ {int /*<<< orphan*/  (* personality ) (int,int,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*) ;} ;
typedef  TYPE_1__ _Unwind_FrameState ;

/* Variables and functions */
 int _UA_CLEANUP_PHASE ; 
 int _UA_END_OF_STACK ; 
 int _UA_FORCE_UNWIND ; 
 int /*<<< orphan*/  _URC_CONTINUE_UNWIND ; 
 int /*<<< orphan*/  _URC_END_OF_STACK ; 
 int /*<<< orphan*/  _URC_FATAL_PHASE2_ERROR ; 
 int /*<<< orphan*/  _URC_INSTALL_CONTEXT ; 
 int /*<<< orphan*/  _URC_NO_REASON ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*,void*) ; 
 int /*<<< orphan*/  stub2 (int,int,int /*<<< orphan*/ ,struct _Unwind_Exception*,struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_advance_context (struct _Unwind_Context*,TYPE_1__*) ; 
 int /*<<< orphan*/  uw_frame_state_for (struct _Unwind_Context*,TYPE_1__*) ; 

__attribute__((used)) static _Unwind_Reason_Code
_Unwind_ForcedUnwind_Phase2 (struct _Unwind_Exception *exc,
			     struct _Unwind_Context *context)
{
  _Unwind_Stop_Fn stop = (_Unwind_Stop_Fn) (_Unwind_Ptr) exc->private_1;
  void *stop_argument = (void *) (_Unwind_Ptr) exc->private_2;
  _Unwind_Reason_Code code, stop_code;

  while (1)
    {
      _Unwind_FrameState fs;
      int action;

      /* Set up fs to describe the FDE for the caller of cur_context.  */
      code = uw_frame_state_for (context, &fs);
      if (code != _URC_NO_REASON && code != _URC_END_OF_STACK)
	return _URC_FATAL_PHASE2_ERROR;

      /* Unwind successful.  */
      action = _UA_FORCE_UNWIND | _UA_CLEANUP_PHASE;
      if (code == _URC_END_OF_STACK)
	action |= _UA_END_OF_STACK;
      stop_code = (*stop) (1, action, exc->exception_class, exc,
			   context, stop_argument);
      if (stop_code != _URC_NO_REASON)
	return _URC_FATAL_PHASE2_ERROR;

      /* Stop didn't want to do anything.  Invoke the personality
	 handler, if applicable, to run cleanups.  */
      if (code == _URC_END_OF_STACK)
	break;
	
      if (fs.personality)
	{
	  code = (*fs.personality) (1, _UA_FORCE_UNWIND | _UA_CLEANUP_PHASE,
				    exc->exception_class, exc, context);
	  if (code == _URC_INSTALL_CONTEXT)
	    break;
	  if (code != _URC_CONTINUE_UNWIND) 
	    return _URC_FATAL_PHASE2_ERROR;
	}

      /* Update cur_context to describe the same frame as fs, and discard
	 the previous context if necessary.  */
      uw_advance_context (context, &fs);
    }

  return code;
}