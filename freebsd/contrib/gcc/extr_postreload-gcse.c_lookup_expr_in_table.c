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
struct expr {int /*<<< orphan*/ * avail_occr; int /*<<< orphan*/  hash; int /*<<< orphan*/  expr; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  expr_obstack ; 
 int /*<<< orphan*/  expr_table ; 
 int /*<<< orphan*/  hash_expr (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,struct expr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct expr*) ; 

__attribute__((used)) static struct expr *
lookup_expr_in_table (rtx pat)
{
  int do_not_record_p;
  struct expr **slot, *tmp_expr;
  hashval_t hash = hash_expr (pat, &do_not_record_p);

  if (do_not_record_p)
    return NULL;

  tmp_expr = (struct expr *) obstack_alloc (&expr_obstack,
					    sizeof (struct expr));
  tmp_expr->expr = pat;
  tmp_expr->hash = hash;
  tmp_expr->avail_occr = NULL;

  slot = (struct expr **) htab_find_slot_with_hash (expr_table, tmp_expr,
                                                    hash, INSERT);
  obstack_free (&expr_obstack, tmp_expr);

  if (!slot)
    return NULL;
  else
    return (*slot);
}