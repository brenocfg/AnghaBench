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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/ * basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 int /*<<< orphan*/  PENDING_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ tree_find_edge_insert_loc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

basic_block
bsi_insert_on_edge_immediate (edge e, tree stmt)
{
  block_stmt_iterator bsi;
  basic_block new_bb = NULL;

  gcc_assert (!PENDING_STMT (e));

  if (tree_find_edge_insert_loc (e, &bsi, &new_bb))
    bsi_insert_after (&bsi, stmt, BSI_NEW_STMT);
  else
    bsi_insert_before (&bsi, stmt, BSI_NEW_STMT);

  return new_bb;
}