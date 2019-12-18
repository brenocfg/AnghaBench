#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bits; size_t word_no; TYPE_1__* elt1; } ;
typedef  TYPE_2__ bitmap_iterator ;
struct TYPE_4__ {int* bits; unsigned int indx; struct TYPE_4__* next; } ;

/* Variables and functions */
 unsigned int BITMAP_ELEMENT_ALL_BITS ; 
 size_t BITMAP_ELEMENT_WORDS ; 
 unsigned int BITMAP_WORD_BITS ; 

__attribute__((used)) static inline bool
bmp_iter_set (bitmap_iterator *bi, unsigned *bit_no)
{
  /* If our current word is nonzero, it contains the bit we want.  */
  if (bi->bits)
    {
    next_bit:
      while (!(bi->bits & 1))
	{
	  bi->bits >>= 1;
	  *bit_no += 1;
	}
      return true;
    }

  /* Round up to the word boundary.  We might have just iterated past
     the end of the last word, hence the -1.  It is not possible for
     bit_no to point at the beginning of the now last word.  */
  *bit_no = ((*bit_no + BITMAP_WORD_BITS - 1)
	     / BITMAP_WORD_BITS * BITMAP_WORD_BITS);
  bi->word_no++;

  while (1)
    {
      /* Find the next nonzero word in this elt.  */
      while (bi->word_no != BITMAP_ELEMENT_WORDS)
	{
	  bi->bits = bi->elt1->bits[bi->word_no];
	  if (bi->bits)
	    goto next_bit;
	  *bit_no += BITMAP_WORD_BITS;
	  bi->word_no++;
	}

      /* Advance to the next element.  */
      bi->elt1 = bi->elt1->next;
      if (!bi->elt1)
	return false;
      *bit_no = bi->elt1->indx * BITMAP_ELEMENT_ALL_BITS;
      bi->word_no = 0;
    }
}