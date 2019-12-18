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
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */
 int /*<<< orphan*/  _Unwind_GetIP (struct _Unwind_Context*) ; 

__attribute__((used)) static inline _Unwind_Ptr
uw_identify_context (struct _Unwind_Context *context)
{
  return _Unwind_GetIP (context);
}