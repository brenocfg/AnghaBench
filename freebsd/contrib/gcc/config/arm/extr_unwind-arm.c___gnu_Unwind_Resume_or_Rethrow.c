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
struct TYPE_6__ {int /*<<< orphan*/ * r; } ;
struct TYPE_7__ {TYPE_1__ core; } ;
typedef  TYPE_2__ phase2_vrs ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;

/* Variables and functions */
 size_t R_LR ; 
 size_t R_PC ; 
 int /*<<< orphan*/  UCB_FORCED_STOP_FN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __gnu_Unwind_RaiseException (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  unwind_phase2_forced (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

_Unwind_Reason_Code
__gnu_Unwind_Resume_or_Rethrow (_Unwind_Control_Block * ucbp,
				phase2_vrs * entry_vrs)
{
  if (!UCB_FORCED_STOP_FN (ucbp))
    return __gnu_Unwind_RaiseException (ucbp, entry_vrs);

  /* Set the pc to the call site.  */
  entry_vrs->core.r[R_PC] = entry_vrs->core.r[R_LR];
  /* Continue unwinding the next frame.  */
  return unwind_phase2_forced (ucbp, entry_vrs, 0);
}