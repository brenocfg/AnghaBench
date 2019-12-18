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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ EXPR_LIST ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_EXPR_LIST_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_INSN_LIST_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_insn_expr_list_list (rtx *listp)
{
  rtx list, next;

  for (list = *listp; list ; list = next)
    {
      next = XEXP (list, 1);
      if (GET_CODE (list) == EXPR_LIST)
	free_EXPR_LIST_node (list);
      else
	free_INSN_LIST_node (list);
    }

  *listp = NULL;
}