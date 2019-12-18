#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct occr {int deleted_p; int /*<<< orphan*/  insn; struct occr* next; } ;
struct expr {int bitmap_index; int /*<<< orphan*/ * reaching_reg; struct occr* antic_occr; struct expr* next_same_hash; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {unsigned int size; struct expr** table; } ;
struct TYPE_4__ {size_t index; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_CUID (int /*<<< orphan*/ ) ; 
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  delete_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 TYPE_2__ expr_hash_table ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  gcse_emit_move_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcse_subst_count ; 
 int /*<<< orphan*/ * gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pre_delete_map ; 
 int /*<<< orphan*/  pre_redundant_insns ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pre_delete (void)
{
  unsigned int i;
  int changed;
  struct expr *expr;
  struct occr *occr;

  changed = 0;
  for (i = 0; i < expr_hash_table.size; i++)
    for (expr = expr_hash_table.table[i];
	 expr != NULL;
	 expr = expr->next_same_hash)
      {
	int indx = expr->bitmap_index;

	/* We only need to search antic_occr since we require
	   ANTLOC != 0.  */

	for (occr = expr->antic_occr; occr != NULL; occr = occr->next)
	  {
	    rtx insn = occr->insn;
	    rtx set;
	    basic_block bb = BLOCK_FOR_INSN (insn);

	    /* We only delete insns that have a single_set.  */
	    if (TEST_BIT (pre_delete_map[bb->index], indx)
		&& (set = single_set (insn)) != 0)
	      {
		/* Create a pseudo-reg to store the result of reaching
		   expressions into.  Get the mode for the new pseudo from
		   the mode of the original destination pseudo.  */
		if (expr->reaching_reg == NULL)
		  expr->reaching_reg
		    = gen_reg_rtx (GET_MODE (SET_DEST (set)));

		gcse_emit_move_after (expr->reaching_reg, SET_DEST (set), insn);
		delete_insn (insn);
		occr->deleted_p = 1;
		SET_BIT (pre_redundant_insns, INSN_CUID (insn));
		changed = 1;
		gcse_subst_count++;

		if (dump_file)
		  {
		    fprintf (dump_file,
			     "PRE: redundant insn %d (expression %d) in ",
			       INSN_UID (insn), indx);
		    fprintf (dump_file, "bb %d, reaching reg is %d\n",
			     bb->index, REGNO (expr->reaching_reg));
		  }
	      }
	  }
      }

  return changed;
}