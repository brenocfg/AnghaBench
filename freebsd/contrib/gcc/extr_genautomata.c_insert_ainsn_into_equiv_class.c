#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ainsn_t ;
struct TYPE_5__ {struct TYPE_5__* next_equiv_class_insn; } ;

/* Variables and functions */

__attribute__((used)) static ainsn_t
insert_ainsn_into_equiv_class (ainsn_t ainsn,
			       ainsn_t cyclic_equiv_class_insn_list)
{
  if (cyclic_equiv_class_insn_list == NULL)
    ainsn->next_equiv_class_insn = ainsn;
  else
    {
      ainsn->next_equiv_class_insn
        = cyclic_equiv_class_insn_list->next_equiv_class_insn;
      cyclic_equiv_class_insn_list->next_equiv_class_insn = ainsn;
    }
  return ainsn;
}