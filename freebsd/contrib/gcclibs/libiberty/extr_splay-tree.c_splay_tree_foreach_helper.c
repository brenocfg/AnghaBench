#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* splay_tree_node ;
typedef  int (* splay_tree_foreach_fn ) (TYPE_1__*,void*) ;
typedef  int /*<<< orphan*/  splay_tree ;
struct TYPE_6__ {struct TYPE_6__* right; struct TYPE_6__* left; } ;

/* Variables and functions */
 int stub1 (TYPE_1__*,void*) ; 

__attribute__((used)) static int
splay_tree_foreach_helper (splay_tree sp, splay_tree_node node,
                           splay_tree_foreach_fn fn, void *data)
{
  int val;

  if (!node)
    return 0;

  val = splay_tree_foreach_helper (sp, node->left, fn, data);
  if (val)
    return val;

  val = (*fn)(node, data);
  if (val)
    return val;

  return splay_tree_foreach_helper (sp, node->right, fn, data);
}