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

/* Variables and functions */
 scalar_t__ RESX_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_reachable_handler (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lookup_stmt_eh_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_eh_edge ; 

void
make_eh_edges (tree stmt)
{
  int region_nr;
  bool is_resx;

  if (TREE_CODE (stmt) == RESX_EXPR)
    {
      region_nr = TREE_INT_CST_LOW (TREE_OPERAND (stmt, 0));
      is_resx = true;
    }
  else
    {
      region_nr = lookup_stmt_eh_region (stmt);
      if (region_nr < 0)
	return;
      is_resx = false;
    }

  foreach_reachable_handler (region_nr, is_resx, make_eh_edge, stmt);
}