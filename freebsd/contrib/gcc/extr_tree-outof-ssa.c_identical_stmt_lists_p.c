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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  PENDING_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  identical_copies_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool 
identical_stmt_lists_p (edge e1, edge e2)
{
  tree t1 = PENDING_STMT (e1);
  tree t2 = PENDING_STMT (e2);
  tree_stmt_iterator tsi1, tsi2;

  gcc_assert (TREE_CODE (t1) == STATEMENT_LIST);
  gcc_assert (TREE_CODE (t2) == STATEMENT_LIST);

  for (tsi1 = tsi_start (t1), tsi2 = tsi_start (t2);
       !tsi_end_p (tsi1) && !tsi_end_p (tsi2); 
       tsi_next (&tsi1), tsi_next (&tsi2))
    {
      if (!identical_copies_p (tsi_stmt (tsi1), tsi_stmt (tsi2)))
        break;
    }

  if (!tsi_end_p (tsi1) || ! tsi_end_p (tsi2))
    return false;

  return true;
}