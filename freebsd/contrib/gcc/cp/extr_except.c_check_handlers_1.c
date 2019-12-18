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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_LOCUS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ can_convert_eh (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 scalar_t__ tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
check_handlers_1 (tree master, tree_stmt_iterator i)
{
  tree type = TREE_TYPE (master);

  for (; !tsi_end_p (i); tsi_next (&i))
    {
      tree handler = tsi_stmt (i);
      if (TREE_TYPE (handler) && can_convert_eh (type, TREE_TYPE (handler)))
	{
	  warning (0, "%Hexception of type %qT will be caught",
		   EXPR_LOCUS (handler), TREE_TYPE (handler));
	  warning (0, "%H   by earlier handler for %qT",
		   EXPR_LOCUS (master), type);
	  break;
	}
    }
}