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
struct TYPE_8__ {struct TYPE_8__* next; struct TYPE_8__* prev; int /*<<< orphan*/  indx; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_9__ {int /*<<< orphan*/  indx; TYPE_1__* current; TYPE_1__* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (TYPE_2__*) ; 
 TYPE_1__* bitmap_element_allocate (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
bitmap_copy (bitmap to, bitmap from)
{
  bitmap_element *from_ptr, *to_ptr = 0;

  bitmap_clear (to);

  /* Copy elements in forward direction one at a time.  */
  for (from_ptr = from->first; from_ptr; from_ptr = from_ptr->next)
    {
      bitmap_element *to_elt = bitmap_element_allocate (to);

      to_elt->indx = from_ptr->indx;
      memcpy (to_elt->bits, from_ptr->bits, sizeof (to_elt->bits));

      /* Here we have a special case of bitmap_element_link, for the case
	 where we know the links are being entered in sequence.  */
      if (to_ptr == 0)
	{
	  to->first = to->current = to_elt;
	  to->indx = from_ptr->indx;
	  to_elt->next = to_elt->prev = 0;
	}
      else
	{
	  to_elt->prev = to_ptr;
	  to_elt->next = 0;
	  to_ptr->next = to_elt;
	}

      to_ptr = to_elt;
    }
}