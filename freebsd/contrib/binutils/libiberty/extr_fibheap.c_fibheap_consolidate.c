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
typedef  TYPE_2__* fibheap_t ;
struct TYPE_16__ {TYPE_1__* min; TYPE_1__* root; } ;
struct TYPE_15__ {int degree; } ;

/* Variables and functions */
 scalar_t__ fibheap_compare (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fibheap_ins_root (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fibheap_link (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fibheap_rem_root (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fibheap_consolidate (fibheap_t heap)
{
  fibnode_t a[1 + 8 * sizeof (long)];
  fibnode_t w;
  fibnode_t y;
  fibnode_t x;
  int i;
  int d;
  int D;

  D = 1 + 8 * sizeof (long);

  memset (a, 0, sizeof (fibnode_t) * D);

  while ((w = heap->root) != NULL)
    {
      x = w;
      fibheap_rem_root (heap, w);
      d = x->degree;
      while (a[d] != NULL)
	{
	  y = a[d];
	  if (fibheap_compare (heap, x, y) > 0)
	    {
	      fibnode_t temp;
	      temp = x;
	      x = y;
	      y = temp;
	    }
	  fibheap_link (heap, y, x);
	  a[d] = NULL;
	  d++;
	}
      a[d] = x;
    }
  heap->min = NULL;
  for (i = 0; i < D; i++)
    if (a[i] != NULL)
      {
	fibheap_ins_root (heap, a[i]);
	if (heap->min == NULL || fibheap_compare (heap, a[i], heap->min) < 0)
	  heap->min = a[i];
      }
}