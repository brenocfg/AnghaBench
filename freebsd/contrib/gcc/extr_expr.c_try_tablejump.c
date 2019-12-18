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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  HAVE_tablejump ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  do_tablejump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
try_tablejump (tree index_type, tree index_expr, tree minval, tree range,
	       rtx table_label, rtx default_label)
{
  rtx index;

  if (! HAVE_tablejump)
    return 0;

  index_expr = fold_build2 (MINUS_EXPR, index_type,
			    fold_convert (index_type, index_expr),
			    fold_convert (index_type, minval));
  index = expand_normal (index_expr);
  do_pending_stack_adjust ();

  do_tablejump (index, TYPE_MODE (index_type),
		convert_modes (TYPE_MODE (index_type),
			       TYPE_MODE (TREE_TYPE (range)),
			       expand_normal (range),
			       TYPE_UNSIGNED (TREE_TYPE (range))),
		table_label, default_label);
  return 1;
}