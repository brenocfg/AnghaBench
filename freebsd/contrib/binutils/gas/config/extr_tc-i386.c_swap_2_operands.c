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
typedef  union i386_op {int dummy; } i386_op ;
typedef  enum bfd_reloc_code_real { ____Placeholder_bfd_reloc_code_real } bfd_reloc_code_real ;
struct TYPE_2__ {unsigned int* types; int* reloc; union i386_op* op; } ;

/* Variables and functions */
 TYPE_1__ i ; 

__attribute__((used)) static void
swap_2_operands (int xchg1, int xchg2)
{
  union i386_op temp_op;
  unsigned int temp_type;
  enum bfd_reloc_code_real temp_reloc;

  temp_type = i.types[xchg2];
  i.types[xchg2] = i.types[xchg1];
  i.types[xchg1] = temp_type;
  temp_op = i.op[xchg2];
  i.op[xchg2] = i.op[xchg1];
  i.op[xchg1] = temp_op;
  temp_reloc = i.reloc[xchg2];
  i.reloc[xchg2] = i.reloc[xchg1];
  i.reloc[xchg1] = temp_reloc;
}