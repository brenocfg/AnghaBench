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
struct function {TYPE_1__* eh; } ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ exc_ptr; } ;

/* Variables and functions */
 struct function* cfun ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 

rtx
get_exception_pointer (struct function *fun)
{
  rtx exc_ptr = fun->eh->exc_ptr;
  if (fun == cfun && ! exc_ptr)
    {
      exc_ptr = gen_reg_rtx (ptr_mode);
      fun->eh->exc_ptr = exc_ptr;
    }
  return exc_ptr;
}