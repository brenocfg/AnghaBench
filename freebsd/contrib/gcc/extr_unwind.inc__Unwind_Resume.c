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
struct _Unwind_Exception {scalar_t__ private_1; } ;
struct _Unwind_Context {int dummy; } ;
typedef  scalar_t__ _Unwind_Reason_Code ;

/* Variables and functions */
 scalar_t__ _URC_INSTALL_CONTEXT ; 
 scalar_t__ _Unwind_ForcedUnwind_Phase2 (struct _Unwind_Exception*,struct _Unwind_Context*) ; 
 scalar_t__ _Unwind_RaiseException_Phase2 (struct _Unwind_Exception*,struct _Unwind_Context*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  uw_init_context (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  uw_install_context (struct _Unwind_Context*,struct _Unwind_Context*) ; 

void
_Unwind_Resume (struct _Unwind_Exception *exc)
{
  struct _Unwind_Context this_context, cur_context;
  _Unwind_Reason_Code code;

  uw_init_context (&this_context);
  cur_context = this_context;

  /* Choose between continuing to process _Unwind_RaiseException
     or _Unwind_ForcedUnwind.  */
  if (exc->private_1 == 0)
    code = _Unwind_RaiseException_Phase2 (exc, &cur_context);
  else
    code = _Unwind_ForcedUnwind_Phase2 (exc, &cur_context);

  gcc_assert (code == _URC_INSTALL_CONTEXT);

  uw_install_context (&this_context, &cur_context);
}