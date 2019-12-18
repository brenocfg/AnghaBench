#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int entry_size; int num_init_entries; TYPE_2__* init_entries; } ;
struct TYPE_9__ {TYPE_1__ insn_table; } ;
struct TYPE_8__ {int /*<<< orphan*/  const* base; } ;
typedef  TYPE_2__ CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_IBASE ;
typedef  TYPE_3__ CGEN_CPU_TABLE ;

/* Variables and functions */
 int MAX_INSNS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mep_cgen_insn_table ; 
 TYPE_2__* xmalloc (int) ; 

__attribute__((used)) static void
build_insn_table (CGEN_CPU_TABLE *cd)
{
  int i;
  const CGEN_IBASE *ib = & mep_cgen_insn_table[0];
  CGEN_INSN *insns = xmalloc (MAX_INSNS * sizeof (CGEN_INSN));

  memset (insns, 0, MAX_INSNS * sizeof (CGEN_INSN));
  for (i = 0; i < MAX_INSNS; ++i)
    insns[i].base = &ib[i];
  cd->insn_table.init_entries = insns;
  cd->insn_table.entry_size = sizeof (CGEN_IBASE);
  cd->insn_table.num_init_entries = MAX_INSNS;
}