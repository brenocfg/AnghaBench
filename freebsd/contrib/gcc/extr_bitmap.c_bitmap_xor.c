#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ indx; int* bits; struct TYPE_14__* next; } ;
typedef  TYPE_2__ bitmap_element ;
typedef  TYPE_3__* bitmap ;
struct TYPE_15__ {TYPE_1__* current; int /*<<< orphan*/  indx; TYPE_2__* first; } ;
struct TYPE_13__ {int /*<<< orphan*/  indx; } ;
typedef  int BITMAP_WORD ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_WORDS ; 
 int /*<<< orphan*/  bitmap_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  bitmap_elt_clear_from (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* bitmap_elt_insert_after (TYPE_3__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void
bitmap_xor (bitmap dst, bitmap a, bitmap b)
{
  bitmap_element *dst_elt = dst->first;
  bitmap_element *a_elt = a->first;
  bitmap_element *b_elt = b->first;
  bitmap_element *dst_prev = NULL;

  gcc_assert (dst != a && dst != b);
  if (a == b)
    {
      bitmap_clear (dst);
      return;
    }

  while (a_elt || b_elt)
    {
      if (a_elt && b_elt && a_elt->indx == b_elt->indx)
	{
	  /* Matching elts, generate A ^ B.  */
	  unsigned ix;
	  BITMAP_WORD ior = 0;

	  if (!dst_elt)
	    dst_elt = bitmap_elt_insert_after (dst, dst_prev, a_elt->indx);
	  else
	    dst_elt->indx = a_elt->indx;
	  for (ix = BITMAP_ELEMENT_WORDS; ix--;)
	    {
	      BITMAP_WORD r = a_elt->bits[ix] ^ b_elt->bits[ix];

	      ior |= r;
	      dst_elt->bits[ix] = r;
	    }
	  a_elt = a_elt->next;
	  b_elt = b_elt->next;
	  if (ior)
	    {
	      dst_prev = dst_elt;
	      dst_elt = dst_elt->next;
	    }
	}
      else
	{
	  /* Copy a single element.  */
	  bitmap_element *src;

	  if (!b_elt || (a_elt && a_elt->indx < b_elt->indx))
	    {
	      src = a_elt;
	      a_elt = a_elt->next;
	    }
	  else
	    {
	      src = b_elt;
	      b_elt = b_elt->next;
	    }

	  if (!dst_elt)
	    dst_elt = bitmap_elt_insert_after (dst, dst_prev, src->indx);
	  else
	    dst_elt->indx = src->indx;
	  memcpy (dst_elt->bits, src->bits, sizeof (dst_elt->bits));
	  dst_prev = dst_elt;
	  dst_elt = dst_elt->next;
	}
    }
  bitmap_elt_clear_from (dst, dst_elt);
  gcc_assert (!dst->current == !dst->first);
  if (dst->current)
    dst->indx = dst->current->indx;
}