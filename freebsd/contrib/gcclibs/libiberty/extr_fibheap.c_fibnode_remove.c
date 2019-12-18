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
typedef  TYPE_2__* fibnode_t ;
struct TYPE_6__ {struct TYPE_6__* right; struct TYPE_6__* left; TYPE_1__* parent; } ;
struct TYPE_5__ {TYPE_2__* child; } ;

/* Variables and functions */

__attribute__((used)) static fibnode_t
fibnode_remove (fibnode_t node)
{
  fibnode_t ret;

  if (node == node->left)
    ret = NULL;
  else
    ret = node->left;

  if (node->parent != NULL && node->parent->child == node)
    node->parent->child = ret;

  node->right->left = node->left;
  node->left->right = node->right;

  node->parent = NULL;
  node->left = node;
  node->right = node;

  return ret;
}