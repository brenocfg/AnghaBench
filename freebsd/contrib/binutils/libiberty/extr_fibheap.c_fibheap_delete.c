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
typedef  TYPE_1__* fibheap_t ;
struct TYPE_6__ {int /*<<< orphan*/ * min; } ;

/* Variables and functions */
 TYPE_1__* fibheap_extr_min_node (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
fibheap_delete (fibheap_t heap)
{
  while (heap->min != NULL)
    free (fibheap_extr_min_node (heap));

  free (heap);
}