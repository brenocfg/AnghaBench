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
struct _Unwind_Context {int /*<<< orphan*/  ra; } ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */
 int _Unwind_IsSignalFrame (struct _Unwind_Context*) ; 

inline _Unwind_Ptr
_Unwind_GetIPInfo (struct _Unwind_Context *context, int *ip_before_insn)
{
  *ip_before_insn = _Unwind_IsSignalFrame (context);
  return (_Unwind_Ptr) context->ra;
}