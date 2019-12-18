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
typedef  int /*<<< orphan*/ * diagnostic_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_special_member_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_ctor_identifier ; 
 int /*<<< orphan*/ * error ; 
 int errorcount ; 
 int /*<<< orphan*/ * warning0 ; 
 int warningcount ; 

__attribute__((used)) static tree
build_temp (tree expr, tree type, int flags,
	    diagnostic_fn_t *diagnostic_fn)
{
  int savew, savee;

  savew = warningcount, savee = errorcount;
  expr = build_special_member_call (NULL_TREE,
				    complete_ctor_identifier,
				    build_tree_list (NULL_TREE, expr),
				    type, flags);
  if (warningcount > savew)
    *diagnostic_fn = warning0;
  else if (errorcount > savee)
    *diagnostic_fn = error;
  else
    *diagnostic_fn = NULL;
  return expr;
}