#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  scalar_t__ fibheapkey_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_16__ {TYPE_1__* min; } ;
struct TYPE_15__ {scalar_t__ key; struct TYPE_15__* parent; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_cascading_cut (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ fibheap_comp_data (TYPE_2__*,scalar_t__,void*,TYPE_1__*) ; 
 scalar_t__ fibheap_compare (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fibheap_cut (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 

void *
fibheap_replace_key_data (fibheap_t heap, fibnode_t node,
                          fibheapkey_t key, void *data)
{
  void *odata;
  fibheapkey_t okey;
  fibnode_t y;

  /* If we wanted to, we could actually do a real increase by redeleting and
     inserting. However, this would require O (log n) time. So just bail out
     for now.  */
  if (fibheap_comp_data (heap, key, data, node) > 0)
    return NULL;

  odata = node->data;
  okey = node->key;
  node->data = data;
  node->key = key;
  y = node->parent;

  if (okey == key)
    return odata;

  /* These two compares are specifically <= 0 to make sure that in the case
     of equality, a node we replaced the data on, becomes the new min.  This
     is needed so that delete's call to extractmin gets the right node.  */
  if (y != NULL && fibheap_compare (heap, node, y) <= 0)
    {
      fibheap_cut (heap, node, y);
      fibheap_cascading_cut (heap, y);
    }

  if (fibheap_compare (heap, node, heap->min) <= 0)
    heap->min = node;

  return odata;
}