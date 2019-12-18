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
struct invariant {struct def* def; } ;
struct df_ref {int flags; struct df_ref* next_ref; } ;
struct df_link {struct df_ref* ref; scalar_t__ next; } ;
struct def {int /*<<< orphan*/  invno; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {struct df_ref* uses; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 TYPE_1__* DF_INSN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_REF_BB (struct df_ref*) ; 
 struct df_link* DF_REF_CHAIN (struct df_ref*) ; 
 struct invariant* DF_REF_DATA (struct df_ref*) ; 
 int DF_REF_READ_WRITE ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_dependencies (rtx insn, bitmap depends_on)
{
  struct df_link *defs;
  struct df_ref *use, *def;
  basic_block bb = BLOCK_FOR_INSN (insn), def_bb;
  struct def *def_data;
  struct invariant *inv;

  for (use = DF_INSN_GET (df, insn)->uses; use; use = use->next_ref)
    {
      if (use->flags & DF_REF_READ_WRITE)
	return false;

      defs = DF_REF_CHAIN (use);
      if (!defs)
	continue;

      if (defs->next)
	return false;

      def = defs->ref;
      inv = DF_REF_DATA (def);
      if (!inv)
	return false;

      def_data = inv->def;
      gcc_assert (def_data != NULL);

      def_bb = DF_REF_BB (def);
      /* Note that in case bb == def_bb, we know that the definition dominates
	 insn, because def has DF_REF_DATA defined and we process the insns
	 in the basic block bb sequentially.  */
      if (!dominated_by_p (CDI_DOMINATORS, bb, def_bb))
	return false;

      bitmap_set_bit (depends_on, def_data->invno);
    }

  return true;
}