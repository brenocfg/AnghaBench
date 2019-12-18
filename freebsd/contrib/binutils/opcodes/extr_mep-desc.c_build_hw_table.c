#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int entry_size; int num_entries; TYPE_2__ const** entries; TYPE_2__ const* init_entries; } ;
struct TYPE_10__ {int machs; TYPE_1__ hw_table; } ;
struct TYPE_9__ {size_t type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ CGEN_HW_ENTRY ;
typedef  TYPE_3__ CGEN_CPU_TABLE ;

/* Variables and functions */
 int CGEN_HW_ATTR_VALUE (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_HW_MACH ; 
 int MAX_HW ; 
 int /*<<< orphan*/  memset (TYPE_2__ const**,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* mep_cgen_hw_table ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
build_hw_table (CGEN_CPU_TABLE *cd)
{
  int i;
  int machs = cd->machs;
  const CGEN_HW_ENTRY *init = & mep_cgen_hw_table[0];
  /* MAX_HW is only an upper bound on the number of selected entries.
     However each entry is indexed by it's enum so there can be holes in
     the table.  */
  const CGEN_HW_ENTRY **selected =
    (const CGEN_HW_ENTRY **) xmalloc (MAX_HW * sizeof (CGEN_HW_ENTRY *));

  cd->hw_table.init_entries = init;
  cd->hw_table.entry_size = sizeof (CGEN_HW_ENTRY);
  memset (selected, 0, MAX_HW * sizeof (CGEN_HW_ENTRY *));
  /* ??? For now we just use machs to determine which ones we want.  */
  for (i = 0; init[i].name != NULL; ++i)
    if (CGEN_HW_ATTR_VALUE (&init[i], CGEN_HW_MACH)
	& machs)
      selected[init[i].type] = &init[i];
  cd->hw_table.entries = selected;
  cd->hw_table.num_entries = MAX_HW;
}