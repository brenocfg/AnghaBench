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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ LABEL_EXPR_LABEL (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
has_label_p (basic_block bb, tree label)
{
  block_stmt_iterator bsi;

  for (bsi = bsi_start (bb); !bsi_end_p (bsi); bsi_next (&bsi))
    {
      tree stmt = bsi_stmt (bsi);

      if (TREE_CODE (stmt) != LABEL_EXPR)
	return false;
      if (LABEL_EXPR_LABEL (stmt) == label)
	return true;
    }
  return false;
}