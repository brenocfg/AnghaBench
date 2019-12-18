#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_8__ {TYPE_1__* root; } ;
struct TYPE_7__ {struct TYPE_7__* right; struct TYPE_7__* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibnode_insert_after (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
fibheap_ins_root (fibheap_t heap, fibnode_t node)
{
  /* If the heap is currently empty, the new node becomes the singleton
     circular root list.  */
  if (heap->root == NULL)
    {
      heap->root = node;
      node->left = node;
      node->right = node;
      return;
    }

  /* Otherwise, insert it in the circular root list between the root
     and it's right node.  */
  fibnode_insert_after (heap->root, node);
}