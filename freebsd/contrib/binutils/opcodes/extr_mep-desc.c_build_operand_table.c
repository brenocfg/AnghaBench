#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int entry_size; int num_entries; TYPE_2__ const** entries; TYPE_2__ const* init_entries; } ;
struct TYPE_11__ {int machs; TYPE_1__ operand_table; } ;
struct TYPE_10__ {size_t type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ CGEN_OPERAND ;
typedef  TYPE_3__ CGEN_CPU_TABLE ;

/* Variables and functions */
 int CGEN_OPERAND_ATTR_VALUE (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_OPERAND_MACH ; 
 int MAX_OPERANDS ; 
 int /*<<< orphan*/  memset (TYPE_2__ const**,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* mep_cgen_operand_table ; 
 TYPE_2__** xmalloc (int) ; 

__attribute__((used)) static void
build_operand_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_OPERAND *init = & mep_cgen_operand_table[0];
  /* MAX_OPERANDS is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_OPERAND **selected = xmalloc (MAX_OPERANDS * sizeof (* selected));

  cd->operand_table.init_entries = init;
  cd->operand_table.entry_size = sizeof (CGEN_OPERAND);
  memset (selected, 0, MAX_OPERANDS * sizeof (CGEN_OPERAND *));
  /* ??? For now we just use mach to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_OPERAND_ATTR_VALUE (&init[i], CGEN_OPERAND_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->operand_table.entries = selected;
  cd->operand_table.num_entries = MAX_OPERANDS;
}