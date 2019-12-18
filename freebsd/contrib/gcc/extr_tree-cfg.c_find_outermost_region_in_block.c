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
struct function {int dummy; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ RESX_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int eh_region_outermost (struct function*,int,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int lookup_stmt_eh_region_fn (struct function*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_outermost_region_in_block (struct function *src_cfun,
				basic_block bb, int region)
{
  block_stmt_iterator si;

  for (si = bsi_start (bb); !bsi_end_p (si); bsi_next (&si))
    {
      tree stmt = bsi_stmt (si);
      int stmt_region;

      if (TREE_CODE (stmt) == RESX_EXPR)
	stmt_region = TREE_INT_CST_LOW (TREE_OPERAND (stmt, 0));
      else
	stmt_region = lookup_stmt_eh_region_fn (src_cfun, stmt);
      if (stmt_region > 0)
	{
	  if (region < 0)
	    region = stmt_region;
	  else if (stmt_region != region)
	    {
	      region = eh_region_outermost (src_cfun, stmt_region, region);
	      gcc_assert (region != -1);
	    }
	}
    }

  return region;
}