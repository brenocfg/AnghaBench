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
struct TYPE_8__ {unsigned int indx; unsigned int* bits; struct TYPE_8__* next; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_9__ {unsigned int indx; TYPE_1__* current; } ;
typedef  unsigned int BITMAP_WORD ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_ALL_BITS ; 
 int BITMAP_ELEMENT_WORDS ; 
 unsigned int BITMAP_WORD_BITS ; 
 int /*<<< orphan*/  bitmap_element_free (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* bitmap_find_bit (TYPE_2__*,unsigned int) ; 

void
bitmap_clear_range (bitmap head, unsigned int start, unsigned int count)
{
  unsigned int first_index = start / BITMAP_ELEMENT_ALL_BITS;
  unsigned int end_bit_plus1 = start + count;
  unsigned int end_bit = end_bit_plus1 - 1;
  unsigned int last_index = (end_bit) / BITMAP_ELEMENT_ALL_BITS;
  bitmap_element *elt = bitmap_find_bit (head, start);

  /* If bitmap_find_bit returns zero, the current is the closest block
     to the result.  If the current is less than first index, find the
     next one.  Otherwise, just set elt to be current.  */
  if (!elt)
    {
      if (head->current)
	{
	  if (head->indx < first_index)
	    {
	      elt = head->current->next;
	      if (!elt)
		return;
	    }
	  else
	    elt = head->current;
	}
      else
	return;
    }

  while (elt && (elt->indx <= last_index))
    {
      bitmap_element * next_elt = elt->next;
      unsigned elt_start_bit = (elt->indx) * BITMAP_ELEMENT_ALL_BITS;
      unsigned elt_end_bit_plus1 = elt_start_bit + BITMAP_ELEMENT_ALL_BITS;


      if (elt_start_bit >= start && elt_end_bit_plus1 <= end_bit_plus1)
	/* Get rid of the entire elt and go to the next one.  */
	bitmap_element_free (head, elt);
      else
	{
	  /* Going to have to knock out some bits in this elt.  */
	  unsigned int first_word_to_mod;
	  BITMAP_WORD first_mask;
	  unsigned int last_word_to_mod;
	  BITMAP_WORD last_mask;
	  unsigned int i;
	  bool clear = true;

	  if (elt_start_bit <= start)
	    {
	      /* The first bit to turn off is somewhere inside this
		 elt.  */
	      first_word_to_mod = (start - elt_start_bit) / BITMAP_WORD_BITS;

	      /* This mask should have 1s in all bits >= start position. */
	      first_mask =
		(((BITMAP_WORD) 1) << ((start % BITMAP_WORD_BITS))) - 1;
	      first_mask = ~first_mask;
	    }
	  else
	    {
	      /* The first bit to turn off is below this start of this elt.  */
	      first_word_to_mod = 0;
	      first_mask = 0;
	      first_mask = ~first_mask;
	    }

	  if (elt_end_bit_plus1 <= end_bit_plus1)
	    {
	      /* The last bit to turn off is beyond this elt.  */
	      last_word_to_mod = BITMAP_ELEMENT_WORDS - 1;
	      last_mask = 0;
	      last_mask = ~last_mask;
	    }
	  else
	    {
	      /* The last bit to turn off is inside to this elt.  */
	      last_word_to_mod =
		(end_bit_plus1 - elt_start_bit) / BITMAP_WORD_BITS;

	      /* The last mask should have 1s below the end bit.  */
	      last_mask =
		(((BITMAP_WORD) 1) << (((end_bit_plus1) % BITMAP_WORD_BITS))) - 1;
	    }


	  if (first_word_to_mod == last_word_to_mod)
	    {
	      BITMAP_WORD mask = first_mask & last_mask;
	      elt->bits[first_word_to_mod] &= ~mask;
	    }
	  else
	    {
	      elt->bits[first_word_to_mod] &= ~first_mask;
	      for (i = first_word_to_mod + 1; i < last_word_to_mod; i++)
		elt->bits[i] = 0;
	      elt->bits[last_word_to_mod] &= ~last_mask;
	    }
	  for (i = 0; i < BITMAP_ELEMENT_WORDS; i++)
	    if (elt->bits[i])
	      {
		clear = false;
		break;
	      }
	  /* Check to see if there are any bits left.  */
	  if (clear)
	    bitmap_element_free (head, elt);
	}
      elt = next_elt;
    }

  if (elt)
    {
      head->current = elt;
      head->indx = head->current->indx;
    }
}