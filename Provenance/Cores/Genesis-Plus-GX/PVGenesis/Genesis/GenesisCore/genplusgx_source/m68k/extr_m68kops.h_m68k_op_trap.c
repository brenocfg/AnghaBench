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

/* Variables and functions */
 scalar_t__ EXCEPTION_TRAP_BASE ; 
 int REG_IR ; 
 int /*<<< orphan*/  m68ki_exception_trapN (scalar_t__) ; 

__attribute__((used)) static void m68k_op_trap(void)
{
  /* Trap#n stacks exception frame type 0 */
  m68ki_exception_trapN(EXCEPTION_TRAP_BASE + (REG_IR & 0xf));  /* HJB 990403 */
}