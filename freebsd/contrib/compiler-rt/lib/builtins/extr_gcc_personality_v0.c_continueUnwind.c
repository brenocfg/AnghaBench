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
struct _Unwind_Exception {int dummy; } ;
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;

/* Variables and functions */
 int /*<<< orphan*/  _URC_CONTINUE_UNWIND ; 
 int /*<<< orphan*/  _URC_FAILURE ; 
 scalar_t__ _URC_OK ; 
 scalar_t__ __gnu_unwind_frame (struct _Unwind_Exception*,struct _Unwind_Context*) ; 

__attribute__((used)) static inline _Unwind_Reason_Code
continueUnwind(struct _Unwind_Exception *exceptionObject,
               struct _Unwind_Context *context) {
#if USING_ARM_EHABI
  // On ARM EHABI the personality routine is responsible for actually
  // unwinding a single stack frame before returning (ARM EHABI Sec. 6.1).
  if (__gnu_unwind_frame(exceptionObject, context) != _URC_OK)
    return _URC_FAILURE;
#endif
  return _URC_CONTINUE_UNWIND;
}