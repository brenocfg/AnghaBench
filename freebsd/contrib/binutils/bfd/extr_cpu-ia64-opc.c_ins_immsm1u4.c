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
struct ia64_operand {int dummy; } ;
typedef  int ia64_insn ;

/* Variables and functions */
 char const* ins_imms_scaled (struct ia64_operand const*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
ins_immsm1u4 (const struct ia64_operand *self, ia64_insn value,
	      ia64_insn *code)
{
  value = ((value & 0xffffffff) ^ 0x80000000) - 0x80000000;

  --value;
  return ins_imms_scaled (self, value, code, 0);
}