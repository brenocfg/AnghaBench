#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _Unwind_Ptr ;
struct TYPE_4__ {int /*<<< orphan*/  fnstart; } ;
struct TYPE_5__ {TYPE_1__ pr_cache; } ;
typedef  TYPE_2__ _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 TYPE_2__* unwind_UCB_from_context (int /*<<< orphan*/ *) ; 

_Unwind_Ptr
_Unwind_GetRegionStart (_Unwind_Context * context)
{
  _Unwind_Control_Block *ucbp;

  ucbp = unwind_UCB_from_context (context);
  return (_Unwind_Ptr) ucbp->pr_cache.fnstart;
}