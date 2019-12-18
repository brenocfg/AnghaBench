#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  scalar_t__ fibheapkey_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_9__ {int /*<<< orphan*/  nodes; TYPE_1__* min; } ;
struct TYPE_8__ {scalar_t__ key; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_ins_root (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* fibnode_new () ; 

fibnode_t
fibheap_insert (fibheap_t heap, fibheapkey_t key, void *data)
{
  fibnode_t node;

  /* Create the new node.  */
  node = fibnode_new ();

  /* Set the node's data.  */
  node->data = data;
  node->key = key;

  /* Insert it into the root list.  */
  fibheap_ins_root (heap, node);

  /* If their was no minimum, or this key is less than the min,
     it's the new min.  */
  if (heap->min == NULL || node->key < heap->min->key)
    heap->min = node;

  heap->nodes++;

  return node;
}