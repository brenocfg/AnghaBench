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
typedef  int /*<<< orphan*/  _Unwind_State ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 int /*<<< orphan*/  __gnu_unwind_pr_common (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

_Unwind_Reason_Code
__aeabi_unwind_cpp_pr1 (_Unwind_State state,
			_Unwind_Control_Block *ucbp,
			_Unwind_Context *context)
{
  return __gnu_unwind_pr_common (state, ucbp, context, 1);
}