#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* bits; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int BITMAP_ELEMENT_WORDS ; 
 int BITMAP_WORD_BITS ; 
 TYPE_1__* bitmap_find_bit (int /*<<< orphan*/ ,int) ; 

int
bitmap_bit_p (bitmap head, int bit)
{
  bitmap_element *ptr;
  unsigned bit_num;
  unsigned word_num;

  ptr = bitmap_find_bit (head, bit);
  if (ptr == 0)
    return 0;

  bit_num = bit % BITMAP_WORD_BITS;
  word_num = bit / BITMAP_WORD_BITS % BITMAP_ELEMENT_WORDS;

  return (ptr->bits[word_num] >> bit_num) & 1;
}