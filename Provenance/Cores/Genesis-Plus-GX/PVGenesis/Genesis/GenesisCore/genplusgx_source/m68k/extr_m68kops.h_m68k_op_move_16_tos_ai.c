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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  OPER_AY_AI_16 () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_set_sr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_move_16_tos_ai(void)
{
  if(FLAG_S)
  {
    uint new_sr = OPER_AY_AI_16();
    m68ki_set_sr(new_sr);
    return;
  }
  m68ki_exception_privilege_violation();
}