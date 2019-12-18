#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* splay_tree_node ;
typedef  TYPE_2__* splay_tree ;
struct TYPE_6__ {TYPE_1__* root; } ;
struct TYPE_5__ {struct TYPE_5__* left; } ;

/* Variables and functions */

splay_tree_node
splay_tree_min (splay_tree sp)
{
  splay_tree_node n = sp->root;

  if (!n)
    return NULL;

  while (n->left)
    n = n->left;

  return n;
}