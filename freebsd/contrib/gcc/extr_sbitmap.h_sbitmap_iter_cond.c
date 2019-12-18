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
struct TYPE_3__ {int word; int* ptr; size_t word_num; size_t size; int bit_num; } ;
typedef  TYPE_1__ sbitmap_iterator ;

/* Variables and functions */
 int SBITMAP_ELT_BITS ; 

__attribute__((used)) static inline bool
sbitmap_iter_cond (sbitmap_iterator *i, unsigned int *n)
{
  /* Skip words that are zeros.  */
  for (; i->word == 0; i->word = i->ptr[i->word_num])
    {
      i->word_num++;

      /* If we have reached the end, break.  */
      if (i->word_num >= i->size)
	return false;

      i->bit_num = i->word_num * SBITMAP_ELT_BITS;
    }

  /* Skip bits that are zero.  */
  for (; (i->word & 1) == 0; i->word >>= 1)
    i->bit_num++;

  *n = i->bit_num;

  return true;
}