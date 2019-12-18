#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ indx; int* bits; struct TYPE_11__* next; } ;
typedef  TYPE_2__ bitmap_element ;
typedef  TYPE_3__* bitmap ;
struct TYPE_12__ {scalar_t__ indx; TYPE_1__* current; TYPE_2__* first; } ;
struct TYPE_10__ {scalar_t__ indx; } ;
typedef  int BITMAP_WORD ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_WORDS ; 
 int /*<<< orphan*/  bitmap_element_free (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bitmap_elt_clear_from (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
bitmap_and_into (bitmap a, bitmap b)
{
  bitmap_element *a_elt = a->first;
  bitmap_element *b_elt = b->first;
  bitmap_element *next;

  if (a == b)
    return;

  while (a_elt && b_elt)
    {
      if (a_elt->indx < b_elt->indx)
	{
	  next = a_elt->next;
	  bitmap_element_free (a, a_elt);
	  a_elt = next;
	}
      else if (b_elt->indx < a_elt->indx)
	b_elt = b_elt->next;
      else
	{
	  /* Matching elts, generate A &= B.  */
	  unsigned ix;
	  BITMAP_WORD ior = 0;

	  for (ix = BITMAP_ELEMENT_WORDS; ix--;)
	    {
	      BITMAP_WORD r = a_elt->bits[ix] & b_elt->bits[ix];

	      a_elt->bits[ix] = r;
	      ior |= r;
	    }
	  next = a_elt->next;
	  if (!ior)
	    bitmap_element_free (a, a_elt);
	  a_elt = next;
	  b_elt = b_elt->next;
	}
    }
  bitmap_elt_clear_from (a, a_elt);
  gcc_assert (!a->current == !a->first);
  gcc_assert (!a->current || a->indx == a->current->indx);
}