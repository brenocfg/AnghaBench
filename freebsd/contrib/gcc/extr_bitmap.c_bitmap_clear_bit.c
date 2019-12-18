#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int* bits; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  unsigned int BITMAP_WORD ;

/* Variables and functions */
 int BITMAP_ELEMENT_WORDS ; 
 int BITMAP_WORD_BITS ; 
 int /*<<< orphan*/  bitmap_element_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ bitmap_element_zerop (TYPE_1__*) ; 
 TYPE_1__* bitmap_find_bit (int /*<<< orphan*/ ,int) ; 

void
bitmap_clear_bit (bitmap head, int bit)
{
  bitmap_element *ptr = bitmap_find_bit (head, bit);

  if (ptr != 0)
    {
      unsigned bit_num  = bit % BITMAP_WORD_BITS;
      unsigned word_num = bit / BITMAP_WORD_BITS % BITMAP_ELEMENT_WORDS;
      ptr->bits[word_num] &= ~ (((BITMAP_WORD) 1) << bit_num);

      /* If we cleared the entire word, free up the element.  */
      if (bitmap_element_zerop (ptr))
	bitmap_element_free (head, ptr);
    }
}