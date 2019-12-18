#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* splay_tree_node ;
struct TYPE_5__ {struct TYPE_5__* left; struct TYPE_5__* right; } ;

/* Variables and functions */

__attribute__((used)) static inline void
rotate_left (splay_tree_node *pp, splay_tree_node p, splay_tree_node n)
{
  splay_tree_node tmp;
  tmp = n->right;
  n->right = p;
  p->left = tmp;
  *pp = n;
}