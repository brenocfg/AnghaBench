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
 int /*<<< orphan*/  AY ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  REG_USP ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 

__attribute__((used)) static void m68k_op_move_32_fru(void)
{
  if(FLAG_S)
  {
    AY = REG_USP;
    return;
  }
  m68ki_exception_privilege_violation();
}