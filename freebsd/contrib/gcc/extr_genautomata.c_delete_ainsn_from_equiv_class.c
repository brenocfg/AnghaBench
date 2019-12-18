#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ainsn_t ;
struct TYPE_3__ {struct TYPE_3__* next_equiv_class_insn; } ;

/* Variables and functions */

__attribute__((used)) static void
delete_ainsn_from_equiv_class (ainsn_t equiv_class_insn)
{
  ainsn_t curr_equiv_class_insn;
  ainsn_t prev_equiv_class_insn;

  prev_equiv_class_insn = equiv_class_insn;
  for (curr_equiv_class_insn = equiv_class_insn->next_equiv_class_insn;
       curr_equiv_class_insn != equiv_class_insn;
       curr_equiv_class_insn = curr_equiv_class_insn->next_equiv_class_insn)
    prev_equiv_class_insn = curr_equiv_class_insn;
  if (prev_equiv_class_insn != equiv_class_insn)
    prev_equiv_class_insn->next_equiv_class_insn
      = equiv_class_insn->next_equiv_class_insn;
}