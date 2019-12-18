#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ (* auto_var_in_fn_p ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ tree_inlining; } ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
find_var_from_fn (tree *tp, int *walk_subtrees, void *data)
{
  tree fn = (tree) data;

  if (TYPE_P (*tp))
    *walk_subtrees = 0;

  else if (DECL_P (*tp)
	   && lang_hooks.tree_inlining.auto_var_in_fn_p (*tp, fn))
    return *tp;

  return NULL_TREE;
}