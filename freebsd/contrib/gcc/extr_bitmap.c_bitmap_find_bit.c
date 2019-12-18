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
struct TYPE_5__ {unsigned int indx; struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_6__ {unsigned int indx; TYPE_1__* current; TYPE_1__* first; } ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_ALL_BITS ; 

__attribute__((used)) static inline bitmap_element *
bitmap_find_bit (bitmap head, unsigned int bit)
{
  bitmap_element *element;
  unsigned int indx = bit / BITMAP_ELEMENT_ALL_BITS;

  if (head->current == 0
      || head->indx == indx)
    return head->current;

  if (head->indx < indx)
    /* INDX is beyond head->indx.  Search from head->current
       forward.  */
    for (element = head->current;
	 element->next != 0 && element->indx < indx;
	 element = element->next)
      ;

  else if (head->indx / 2 < indx)
    /* INDX is less than head->indx and closer to head->indx than to
       0.  Search from head->current backward.  */
    for (element = head->current;
	 element->prev != 0 && element->indx > indx;
	 element = element->prev)
      ;

  else
    /* INDX is less than head->indx and closer to 0 than to
       head->indx.  Search from head->first forward.  */
    for (element = head->first;
	 element->next != 0 && element->indx < indx;
	 element = element->next)
      ;

  /* `element' is the nearest to the one we want.  If it's not the one we
     want, the one we want doesn't exist.  */
  head->current = element;
  head->indx = element->indx;
  if (element != 0 && element->indx != indx)
    element = 0;

  return element;
}