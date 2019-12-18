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
struct finally_tree_node {int /*<<< orphan*/  parent; int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int /*<<< orphan*/  finally_tree ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct finally_tree_node*) ; 

__attribute__((used)) static bool
outside_finally_tree (tree start, tree target)
{
  struct finally_tree_node n, *p;

  do
    {
      n.child = start;
      p = (struct finally_tree_node *) htab_find (finally_tree, &n);
      if (!p)
	return true;
      start = p->parent;
    }
  while (start != target);

  return false;
}