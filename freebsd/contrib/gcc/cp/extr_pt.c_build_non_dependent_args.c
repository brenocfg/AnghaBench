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

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  build_non_dependent_expr (int /*<<< orphan*/ ) ; 
 scalar_t__ nreverse (scalar_t__) ; 
 scalar_t__ tree_cons (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

tree
build_non_dependent_args (tree args)
{
  tree a;
  tree new_args;

  new_args = NULL_TREE;
  for (a = args; a; a = TREE_CHAIN (a))
    new_args = tree_cons (NULL_TREE,
			  build_non_dependent_expr (TREE_VALUE (a)),
			  new_args);
  return nreverse (new_args);
}