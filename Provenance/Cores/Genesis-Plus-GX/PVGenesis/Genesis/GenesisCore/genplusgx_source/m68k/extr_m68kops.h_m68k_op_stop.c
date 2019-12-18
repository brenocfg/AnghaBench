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
typedef  int /*<<< orphan*/  uint ;
struct TYPE_2__ {scalar_t__ cycle_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_STOPPED ; 
 scalar_t__ FLAG_S ; 
 int MUL ; 
 int /*<<< orphan*/  OPER_I_16 () ; 
 int /*<<< orphan*/  SET_CYCLES (scalar_t__) ; 
 int /*<<< orphan*/  STOP_LEVEL_STOP ; 
 TYPE_1__ m68ki_cpu ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_set_sr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_stop(void)
{
  if(FLAG_S)
  {
    uint new_sr = OPER_I_16();
    CPU_STOPPED |= STOP_LEVEL_STOP;
    m68ki_set_sr(new_sr);
    SET_CYCLES(m68ki_cpu.cycle_end - 4*MUL); 
    return;
  }
  m68ki_exception_privilege_violation();
}