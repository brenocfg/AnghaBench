#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* elements; } ;
typedef  TYPE_1__ bitmap_obstack ;
struct TYPE_8__ {scalar_t__ indx; struct TYPE_8__* prev; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ bitmap_element ;
typedef  TYPE_3__* bitmap ;
struct TYPE_9__ {scalar_t__ indx; TYPE_2__* current; int /*<<< orphan*/ * first; TYPE_1__* obstack; } ;

/* Variables and functions */
 TYPE_2__* bitmap_ggc_free ; 

void
bitmap_elt_clear_from (bitmap head, bitmap_element *elt)
{
  bitmap_element *prev;
  bitmap_obstack *bit_obstack = head->obstack;

  if (!elt) return;

  prev = elt->prev;
  if (prev)
    {
      prev->next = NULL;
      if (head->current->indx > prev->indx)
	{
	  head->current = prev;
	  head->indx = prev->indx;
	}
    }
  else
    {
      head->first = NULL;
      head->current = NULL;
      head->indx = 0;
    }

  /* Put the entire list onto the free list in one operation. */
  if (bit_obstack)
    {
      elt->prev = bit_obstack->elements;
      bit_obstack->elements = elt;
    }
  else
    {
      elt->prev = bitmap_ggc_free;
      bitmap_ggc_free = elt;
    }
}