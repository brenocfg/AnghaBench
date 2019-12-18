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
struct loop {scalar_t__ header; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  scalar_t__ basic_block ;
typedef  int /*<<< orphan*/  LOC ;

/* Variables and functions */
 scalar_t__ EXPR_FILENAME (scalar_t__) ; 
 scalar_t__ EXPR_HAS_LOCATION (scalar_t__) ; 
 scalar_t__ EXPR_LINENO (scalar_t__) ; 
 int /*<<< orphan*/  EXPR_LOC (scalar_t__) ; 
 scalar_t__ EXPR_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  UNKNOWN_LOC ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (scalar_t__) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ get_loop_exit_condition (struct loop*) ; 

LOC
find_loop_location (struct loop *loop)
{
  tree node = NULL_TREE;
  basic_block bb;
  block_stmt_iterator si;

  if (!loop)
    return UNKNOWN_LOC;

  node = get_loop_exit_condition (loop);

  if (node && EXPR_P (node) && EXPR_HAS_LOCATION (node)
      && EXPR_FILENAME (node) && EXPR_LINENO (node))
    return EXPR_LOC (node);

  /* If we got here the loop is probably not "well formed",
     try to estimate the loop location */

  if (!loop->header)
    return UNKNOWN_LOC;

  bb = loop->header;

  for (si = bsi_start (bb); !bsi_end_p (si); bsi_next (&si))
    {
      node = bsi_stmt (si);
      if (node && EXPR_P (node) && EXPR_HAS_LOCATION (node))
        return EXPR_LOC (node);
    }

  return UNKNOWN_LOC;
}