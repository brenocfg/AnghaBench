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
struct expr {struct occr* avail_occr; int /*<<< orphan*/  hash; void* expr; } ;
typedef  void* rtx ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 scalar_t__ BLOCK_NUM (void*) ; 
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  expr_obstack ; 
 int /*<<< orphan*/  expr_table ; 
 int /*<<< orphan*/  hash_expr (void*,int*) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,struct expr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct expr*) ; 
 int /*<<< orphan*/  occr_obstack ; 

__attribute__((used)) static void
insert_expr_in_table (rtx x, rtx insn)
{
  int do_not_record_p;
  hashval_t hash;
  struct expr *cur_expr, **slot;
  struct occr *avail_occr, *last_occr = NULL;

  hash = hash_expr (x, &do_not_record_p);

  /* Do not insert expression in the table if it contains volatile operands,
     or if hash_expr determines the expression is something we don't want
     to or can't handle.  */
  if (do_not_record_p)
    return;

  /* We anticipate that redundant expressions are rare, so for convenience
     allocate a new hash table element here already and set its fields.
     If we don't do this, we need a hack with a static struct expr.  Anyway,
     obstack_free is really fast and one more obstack_alloc doesn't hurt if
     we're going to see more expressions later on.  */
  cur_expr = (struct expr *) obstack_alloc (&expr_obstack,
					    sizeof (struct expr));
  cur_expr->expr = x;
  cur_expr->hash = hash;
  cur_expr->avail_occr = NULL;

  slot = (struct expr **) htab_find_slot_with_hash (expr_table, cur_expr,
						    hash, INSERT);
  
  if (! (*slot))
    /* The expression isn't found, so insert it.  */
    *slot = cur_expr;
  else
    {
      /* The expression is already in the table, so roll back the
	 obstack and use the existing table entry.  */
      obstack_free (&expr_obstack, cur_expr);
      cur_expr = *slot;
    }

  /* Search for another occurrence in the same basic block.  */
  avail_occr = cur_expr->avail_occr;
  while (avail_occr && BLOCK_NUM (avail_occr->insn) != BLOCK_NUM (insn))
    {
      /* If an occurrence isn't found, save a pointer to the end of
	 the list.  */
      last_occr = avail_occr;
      avail_occr = avail_occr->next;
    }

  if (avail_occr)
    /* Found another instance of the expression in the same basic block.
       Prefer this occurrence to the currently recorded one.  We want
       the last one in the block and the block is scanned from start
       to end.  */
    avail_occr->insn = insn;
  else
    {
      /* First occurrence of this expression in this basic block.  */
      avail_occr = (struct occr *) obstack_alloc (&occr_obstack,
						  sizeof (struct occr));

      /* First occurrence of this expression in any block?  */
      if (cur_expr->avail_occr == NULL)
        cur_expr->avail_occr = avail_occr;
      else
        last_occr->next = avail_occr;

      avail_occr->insn = insn;
      avail_occr->next = NULL;
      avail_occr->deleted_p = 0;
    }
}