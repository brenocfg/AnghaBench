#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct occr {void* insn; scalar_t__ deleted_p; struct occr* next; } ;
struct hash_table {int /*<<< orphan*/  n_elems; struct expr** table; int /*<<< orphan*/  size; } ;
struct expr {struct occr* avail_occr; int /*<<< orphan*/ * antic_occr; struct expr* next_same_hash; scalar_t__ bitmap_index; int /*<<< orphan*/  expr; } ;
typedef  void* rtx ;

/* Variables and functions */
 scalar_t__ BLOCK_NUM (void*) ; 
 scalar_t__ GET_CODE (void*) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (void*) ; 
 int bytes_used ; 
 int /*<<< orphan*/  copy_rtx (void*) ; 
 int expr_equiv_p (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void* gcse_alloc (int) ; 
 unsigned int hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_set_in_table (rtx x, rtx insn, struct hash_table *table)
{
  int found;
  unsigned int hash;
  struct expr *cur_expr, *last_expr = NULL;
  struct occr *cur_occr;

  gcc_assert (GET_CODE (x) == SET && REG_P (SET_DEST (x)));

  hash = hash_set (REGNO (SET_DEST (x)), table->size);

  cur_expr = table->table[hash];
  found = 0;

  while (cur_expr && 0 == (found = expr_equiv_p (cur_expr->expr, x)))
    {
      /* If the expression isn't found, save a pointer to the end of
	 the list.  */
      last_expr = cur_expr;
      cur_expr = cur_expr->next_same_hash;
    }

  if (! found)
    {
      cur_expr = gcse_alloc (sizeof (struct expr));
      bytes_used += sizeof (struct expr);
      if (table->table[hash] == NULL)
	/* This is the first pattern that hashed to this index.  */
	table->table[hash] = cur_expr;
      else
	/* Add EXPR to end of this hash chain.  */
	last_expr->next_same_hash = cur_expr;

      /* Set the fields of the expr element.
	 We must copy X because it can be modified when copy propagation is
	 performed on its operands.  */
      cur_expr->expr = copy_rtx (x);
      cur_expr->bitmap_index = table->n_elems++;
      cur_expr->next_same_hash = NULL;
      cur_expr->antic_occr = NULL;
      cur_expr->avail_occr = NULL;
    }

  /* Now record the occurrence.  */
  cur_occr = cur_expr->avail_occr;

  if (cur_occr && BLOCK_NUM (cur_occr->insn) == BLOCK_NUM (insn))
    {
      /* Found another instance of the expression in the same basic block.
	 Prefer this occurrence to the currently recorded one.  We want
	 the last one in the block and the block is scanned from start
	 to end.  */
      cur_occr->insn = insn;
    }
  else
    {
      /* First occurrence of this expression in this basic block.  */
      cur_occr = gcse_alloc (sizeof (struct occr));
      bytes_used += sizeof (struct occr);

	  cur_occr->insn = insn;
	  cur_occr->next = cur_expr->avail_occr;
	  cur_occr->deleted_p = 0;
	  cur_expr->avail_occr = cur_occr;
    }
}