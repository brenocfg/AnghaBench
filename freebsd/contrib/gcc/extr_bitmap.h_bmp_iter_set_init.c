#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int word_no; unsigned int bits; TYPE_5__* elt1; int /*<<< orphan*/ * elt2; } ;
typedef  TYPE_1__ bitmap_iterator ;
typedef  TYPE_2__* bitmap ;
struct TYPE_8__ {unsigned int indx; unsigned int* bits; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_5__* first; } ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_ALL_BITS ; 
 unsigned int BITMAP_ELEMENT_WORDS ; 
 unsigned int BITMAP_WORD_BITS ; 
 TYPE_5__ bitmap_zero_bits ; 

__attribute__((used)) static inline void
bmp_iter_set_init (bitmap_iterator *bi, bitmap map,
		   unsigned start_bit, unsigned *bit_no)
{
  bi->elt1 = map->first;
  bi->elt2 = NULL;

  /* Advance elt1 until it is not before the block containing start_bit.  */
  while (1)
    {
      if (!bi->elt1)
	{
	  bi->elt1 = &bitmap_zero_bits;
	  break;
	}

      if (bi->elt1->indx >= start_bit / BITMAP_ELEMENT_ALL_BITS)
	break;
      bi->elt1 = bi->elt1->next;
    }

  /* We might have gone past the start bit, so reinitialize it.  */
  if (bi->elt1->indx != start_bit / BITMAP_ELEMENT_ALL_BITS)
    start_bit = bi->elt1->indx * BITMAP_ELEMENT_ALL_BITS;

  /* Initialize for what is now start_bit.  */
  bi->word_no = start_bit / BITMAP_WORD_BITS % BITMAP_ELEMENT_WORDS;
  bi->bits = bi->elt1->bits[bi->word_no];
  bi->bits >>= start_bit % BITMAP_WORD_BITS;

  /* If this word is zero, we must make sure we're not pointing at the
     first bit, otherwise our incrementing to the next word boundary
     will fail.  It won't matter if this increment moves us into the
     next word.  */
  start_bit += !bi->bits;

  *bit_no = start_bit;
}