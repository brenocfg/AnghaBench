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
struct ls_expr {unsigned int hash_index; struct ls_expr* next; struct expr* expr; int /*<<< orphan*/  pattern; int /*<<< orphan*/  invalid; } ;
struct expr {int /*<<< orphan*/  expr; struct expr* next_same_hash; } ;
struct TYPE_2__ {unsigned int size; struct expr** table; } ;

/* Variables and functions */
 scalar_t__ dump_file ; 
 scalar_t__ expr_equiv_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ expr_hash_table ; 
 int /*<<< orphan*/  free_ldst_entry (struct ls_expr*) ; 
 int /*<<< orphan*/  htab_remove_elt_with_hash (int /*<<< orphan*/ ,struct ls_expr*,unsigned int) ; 
 struct ls_expr* pre_ldst_mems ; 
 int /*<<< orphan*/  pre_ldst_table ; 
 int /*<<< orphan*/  print_ldst_list (scalar_t__) ; 

__attribute__((used)) static void
trim_ld_motion_mems (void)
{
  struct ls_expr * * last = & pre_ldst_mems;
  struct ls_expr * ptr = pre_ldst_mems;

  while (ptr != NULL)
    {
      struct expr * expr;

      /* Delete if entry has been made invalid.  */
      if (! ptr->invalid)
	{
	  /* Delete if we cannot find this mem in the expression list.  */
	  unsigned int hash = ptr->hash_index % expr_hash_table.size;

	  for (expr = expr_hash_table.table[hash];
	       expr != NULL;
	       expr = expr->next_same_hash)
	    if (expr_equiv_p (expr->expr, ptr->pattern))
	      break;
	}
      else
	expr = (struct expr *) 0;

      if (expr)
	{
	  /* Set the expression field if we are keeping it.  */
	  ptr->expr = expr;
	  last = & ptr->next;
	  ptr = ptr->next;
	}
      else
	{
	  *last = ptr->next;
	  htab_remove_elt_with_hash (pre_ldst_table, ptr, ptr->hash_index);
	  free_ldst_entry (ptr);
	  ptr = * last;
	}
    }

  /* Show the world what we've found.  */
  if (dump_file && pre_ldst_mems != NULL)
    print_ldst_list (dump_file);
}