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
struct _Unwind_Context {int /*<<< orphan*/  rp; } ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */

inline _Unwind_Ptr
_Unwind_GetIP (struct _Unwind_Context *context)
{
  return context->rp;
}