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
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_phi_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_stmt_or_phi (tree t)
{
  if (TREE_CODE (t) == PHI_NODE)
    remove_phi_node (t, NULL);
  else
    {
      block_stmt_iterator bsi = bsi_for_stmt (t);
      bsi_remove (&bsi, true);
    }
}