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
struct _Unwind_Context {int dummy; } ;
typedef  scalar_t__ (* _Unwind_Trace_Fn ) (struct _Unwind_Context*,void*) ;
typedef  scalar_t__ _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_FrameState ;

/* Variables and functions */
 scalar_t__ _URC_END_OF_STACK ; 
 scalar_t__ _URC_FATAL_PHASE1_ERROR ; 
 scalar_t__ _URC_NO_REASON ; 
 scalar_t__ stub1 (struct _Unwind_Context*,void*) ; 
 scalar_t__ uw_frame_state_for (struct _Unwind_Context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uw_init_context (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_update_context (struct _Unwind_Context*,int /*<<< orphan*/ *) ; 

_Unwind_Reason_Code
_Unwind_Backtrace(_Unwind_Trace_Fn trace, void * trace_argument)
{
  struct _Unwind_Context context;
  _Unwind_Reason_Code code;

  uw_init_context (&context);

  while (1)
    {
      _Unwind_FrameState fs;

      /* Set up fs to describe the FDE for the caller of context.  */
      code = uw_frame_state_for (&context, &fs);
      if (code != _URC_NO_REASON && code != _URC_END_OF_STACK)
	return _URC_FATAL_PHASE1_ERROR;

      /* Call trace function.  */
      if ((*trace) (&context, trace_argument) != _URC_NO_REASON)
	return _URC_FATAL_PHASE1_ERROR;

      /* We're done at end of stack.  */	
      if (code == _URC_END_OF_STACK)
	break;

      /* Update context to describe the same frame as fs.  */
      uw_update_context (&context, &fs);
    }

  return code;
}