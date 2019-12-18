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
struct TYPE_5__ {int indx; unsigned int* bits; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  unsigned int BITMAP_WORD ;

/* Variables and functions */
 int BITMAP_ELEMENT_ALL_BITS ; 
 int BITMAP_ELEMENT_WORDS ; 
 int BITMAP_WORD_BITS ; 
 TYPE_1__* bitmap_element_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_element_link (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* bitmap_find_bit (int /*<<< orphan*/ ,int) ; 

void
bitmap_set_bit (bitmap head, int bit)
{
  bitmap_element *ptr = bitmap_find_bit (head, bit);
  unsigned word_num = bit / BITMAP_WORD_BITS % BITMAP_ELEMENT_WORDS;
  unsigned bit_num  = bit % BITMAP_WORD_BITS;
  BITMAP_WORD bit_val = ((BITMAP_WORD) 1) << bit_num;

  if (ptr == 0)
    {
      ptr = bitmap_element_allocate (head);
      ptr->indx = bit / BITMAP_ELEMENT_ALL_BITS;
      ptr->bits[word_num] = bit_val;
      bitmap_element_link (head, ptr);
    }
  else
    ptr->bits[word_num] |= bit_val;
}