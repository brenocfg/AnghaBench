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
struct TYPE_8__ {int /*<<< orphan*/ * min; } ;
struct TYPE_7__ {void* data; } ;

/* Variables and functions */
 TYPE_1__* fibheap_extr_min_node (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void *
fibheap_extract_min (fibheap_t heap)
{
  fibnode_t z;
  void *ret = NULL;

  /* If we don't have a min set, it means we have no nodes.  */
  if (heap->min != NULL)
    {
      /* Otherwise, extract the min node, free the node, and return the
         node's data.  */
      z = fibheap_extr_min_node (heap);
      ret = z->data;
      free (z);
    }

  return ret;
}