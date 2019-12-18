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
typedef  int ia64_insn ;
struct TYPE_2__ {int mask; int bits; int offset; } ;

/* Variables and functions */
 TYPE_1__* completer_table ; 

__attribute__((used)) static ia64_insn
apply_completer (ia64_insn opcode, int completer_index)
{
  ia64_insn mask = completer_table[completer_index].mask;
  ia64_insn bits = completer_table[completer_index].bits;
  int shiftamt = (completer_table[completer_index].offset & 63);

  mask = mask << shiftamt;
  bits = bits << shiftamt;
  opcode = (opcode & ~mask) | bits;
  return opcode;
}