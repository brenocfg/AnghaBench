#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct _Unwind_Context {TYPE_1__ bases; } ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */

_Unwind_Ptr
_Unwind_GetRegionStart (struct _Unwind_Context *context)
{
  return (_Unwind_Ptr) context->bases.func;
}