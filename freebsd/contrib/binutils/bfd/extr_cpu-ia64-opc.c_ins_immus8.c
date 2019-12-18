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
 char const* ins_immu (struct ia64_operand const*,int,int*) ; 

__attribute__((used)) static const char*
ins_immus8 (const struct ia64_operand *self, ia64_insn value, ia64_insn *code)
{
  if (value & 0x7)
    return "value not an integer multiple of 8";
  return ins_immu (self, value >> 3, code);
}