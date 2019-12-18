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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SKIP_TRAMPOLINE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  find_objc_msgcall (scalar_t__,scalar_t__*) ; 

__attribute__((used)) static CORE_ADDR 
objc_skip_trampoline (CORE_ADDR stop_pc)
{
  CORE_ADDR real_stop_pc;
  CORE_ADDR method_stop_pc;
  
  real_stop_pc = SKIP_TRAMPOLINE_CODE (stop_pc);

  if (real_stop_pc != 0)
    find_objc_msgcall (real_stop_pc, &method_stop_pc);
  else
    find_objc_msgcall (stop_pc, &method_stop_pc);

  if (method_stop_pc)
    {
      real_stop_pc = SKIP_TRAMPOLINE_CODE (method_stop_pc);
      if (real_stop_pc == 0)
	real_stop_pc = method_stop_pc;
    }

  return real_stop_pc;
}