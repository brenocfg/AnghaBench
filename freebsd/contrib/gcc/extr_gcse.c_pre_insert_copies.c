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
struct occr {int copied_p; int /*<<< orphan*/  insn; struct occr* next; int /*<<< orphan*/  deleted_p; } ;
struct expr {struct occr* avail_occr; struct occr* antic_occr; int /*<<< orphan*/ * reaching_reg; struct expr* next_same_hash; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {unsigned int size; struct expr** table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_CUID (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ expr_hash_table ; 
 int /*<<< orphan*/  pre_expr_reaches_here_p (int /*<<< orphan*/ ,struct expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_insert_copy_insn (struct expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_redundant_insns ; 
 int /*<<< orphan*/  update_ld_motion_stores (struct expr*) ; 

__attribute__((used)) static void
pre_insert_copies (void)
{
  unsigned int i, added_copy;
  struct expr *expr;
  struct occr *occr;
  struct occr *avail;

  /* For each available expression in the table, copy the result to
     `reaching_reg' if the expression reaches a deleted one.

     ??? The current algorithm is rather brute force.
     Need to do some profiling.  */

  for (i = 0; i < expr_hash_table.size; i++)
    for (expr = expr_hash_table.table[i]; expr != NULL; expr = expr->next_same_hash)
      {
	/* If the basic block isn't reachable, PPOUT will be TRUE.  However,
	   we don't want to insert a copy here because the expression may not
	   really be redundant.  So only insert an insn if the expression was
	   deleted.  This test also avoids further processing if the
	   expression wasn't deleted anywhere.  */
	if (expr->reaching_reg == NULL)
	  continue;

	/* Set when we add a copy for that expression.  */
	added_copy = 0;

	for (occr = expr->antic_occr; occr != NULL; occr = occr->next)
	  {
	    if (! occr->deleted_p)
	      continue;

	    for (avail = expr->avail_occr; avail != NULL; avail = avail->next)
	      {
		rtx insn = avail->insn;

		/* No need to handle this one if handled already.  */
		if (avail->copied_p)
		  continue;

		/* Don't handle this one if it's a redundant one.  */
		if (TEST_BIT (pre_redundant_insns, INSN_CUID (insn)))
		  continue;

		/* Or if the expression doesn't reach the deleted one.  */
		if (! pre_expr_reaches_here_p (BLOCK_FOR_INSN (avail->insn),
					       expr,
					       BLOCK_FOR_INSN (occr->insn)))
		  continue;

                added_copy = 1;

		/* Copy the result of avail to reaching_reg.  */
		pre_insert_copy_insn (expr, insn);
		avail->copied_p = 1;
	      }
	  }

	  if (added_copy)
            update_ld_motion_stores (expr);
      }
}