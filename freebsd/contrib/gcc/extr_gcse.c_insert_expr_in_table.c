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
struct expr {struct occr* avail_occr; struct occr* antic_occr; struct expr* next_same_hash; scalar_t__ bitmap_index; void* expr; } ;
typedef  void* rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BLOCK_NUM (void*) ; 
 int bytes_used ; 
 int expr_equiv_p (void*,void*) ; 
 void* gcse_alloc (int) ; 
 unsigned int hash_expr (void*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_expr_in_table (rtx x, enum machine_mode mode, rtx insn, int antic_p,
		      int avail_p, struct hash_table *table)
{
  int found, do_not_record_p;
  unsigned int hash;
  struct expr *cur_expr, *last_expr = NULL;
  struct occr *antic_occr, *avail_occr;

  hash = hash_expr (x, mode, &do_not_record_p, table->size);

  /* Do not insert expression in table if it contains volatile operands,
     or if hash_expr determines the expression is something we don't want
     to or can't handle.  */
  if (do_not_record_p)
    return;

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

      /* Set the fields of the expr element.  */
      cur_expr->expr = x;
      cur_expr->bitmap_index = table->n_elems++;
      cur_expr->next_same_hash = NULL;
      cur_expr->antic_occr = NULL;
      cur_expr->avail_occr = NULL;
    }

  /* Now record the occurrence(s).  */
  if (antic_p)
    {
      antic_occr = cur_expr->antic_occr;

      if (antic_occr && BLOCK_NUM (antic_occr->insn) != BLOCK_NUM (insn))
	antic_occr = NULL;

      if (antic_occr)
	/* Found another instance of the expression in the same basic block.
	   Prefer the currently recorded one.  We want the first one in the
	   block and the block is scanned from start to end.  */
	; /* nothing to do */
      else
	{
	  /* First occurrence of this expression in this basic block.  */
	  antic_occr = gcse_alloc (sizeof (struct occr));
	  bytes_used += sizeof (struct occr);
	  antic_occr->insn = insn;
	  antic_occr->next = cur_expr->antic_occr;
	  antic_occr->deleted_p = 0;
	  cur_expr->antic_occr = antic_occr;
	}
    }

  if (avail_p)
    {
      avail_occr = cur_expr->avail_occr;

      if (avail_occr && BLOCK_NUM (avail_occr->insn) == BLOCK_NUM (insn))
	{
	  /* Found another instance of the expression in the same basic block.
	     Prefer this occurrence to the currently recorded one.  We want
	     the last one in the block and the block is scanned from start
	     to end.  */
	  avail_occr->insn = insn;
	}
      else
	{
	  /* First occurrence of this expression in this basic block.  */
	  avail_occr = gcse_alloc (sizeof (struct occr));
	  bytes_used += sizeof (struct occr);
	  avail_occr->insn = insn;
	  avail_occr->next = cur_expr->avail_occr;
	  avail_occr->deleted_p = 0;
	  cur_expr->avail_occr = avail_occr;
	}
    }
}