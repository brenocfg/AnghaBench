#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_init_entries; TYPE_2__* new_entries; } ;
struct TYPE_7__ {TYPE_1__ macro_insn_table; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ CGEN_INSN_LIST ;
typedef  TYPE_3__* CGEN_CPU_DESC ;

/* Variables and functions */

int
cgen_macro_insn_count (CGEN_CPU_DESC cd)
{
  int count = cd->macro_insn_table.num_init_entries;
  CGEN_INSN_LIST *rt_insns = cd->macro_insn_table.new_entries;

  for ( ; rt_insns != NULL; rt_insns = rt_insns->next)
    ++count;

  return count;
}