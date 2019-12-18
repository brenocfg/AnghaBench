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
struct ls_expr {struct ls_expr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ldst_entry (struct ls_expr*) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 struct ls_expr* pre_ldst_mems ; 
 int /*<<< orphan*/ * pre_ldst_table ; 

__attribute__((used)) static void
free_ldst_mems (void)
{
  if (pre_ldst_table)
    htab_delete (pre_ldst_table);
  pre_ldst_table = NULL;

  while (pre_ldst_mems)
    {
      struct ls_expr * tmp = pre_ldst_mems;

      pre_ldst_mems = pre_ldst_mems->next;

      free_ldst_entry (tmp);
    }

  pre_ldst_mems = NULL;
}