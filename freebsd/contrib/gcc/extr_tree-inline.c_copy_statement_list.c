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

/* Variables and functions */
 int /*<<< orphan*/  TSI_NEW_STMT ; 
 int /*<<< orphan*/  alloc_stmt_list () ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_statement_list (tree *tp)
{
  tree_stmt_iterator oi, ni;
  tree new;

  new = alloc_stmt_list ();
  ni = tsi_start (new);
  oi = tsi_start (*tp);
  *tp = new;

  for (; !tsi_end_p (oi); tsi_next (&oi))
    tsi_link_after (&ni, tsi_stmt (oi), TSI_NEW_STMT);
}