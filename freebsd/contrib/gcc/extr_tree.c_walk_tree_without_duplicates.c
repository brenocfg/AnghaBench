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
typedef  int /*<<< orphan*/  walk_tree_fn ;
typedef  int /*<<< orphan*/  tree ;
struct pointer_set_t {int dummy; } ;

/* Variables and functions */
 struct pointer_set_t* pointer_set_create () ; 
 int /*<<< orphan*/  pointer_set_destroy (struct pointer_set_t*) ; 
 int /*<<< orphan*/  walk_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,struct pointer_set_t*) ; 

tree
walk_tree_without_duplicates (tree *tp, walk_tree_fn func, void *data)
{
  tree result;
  struct pointer_set_t *pset;

  pset = pointer_set_create ();
  result = walk_tree (tp, func, data, pset);
  pointer_set_destroy (pset);
  return result;
}