#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t alloc_type ;

/* Variables and functions */
 int BYTES_PER_ALLOC_BIT ; 
 int alloc_ffs (size_t) ; 

__attribute__((used)) static inline size_t
zone_object_size_1 (alloc_type *alloc_bits,
		    size_t start_word, size_t start_bit,
		    size_t max_size)
{
  size_t size;
  alloc_type alloc_word;
  int indx;

  /* Load the first word.  */
  alloc_word = alloc_bits[start_word++];

  /* If that was the last bit in this word, we'll want to continue
     with the next word.  Otherwise, handle the rest of this word.  */
  if (start_bit)
    {
      indx = alloc_ffs (alloc_word >> start_bit);
      if (indx)
	/* indx is 1-based.  We started at the bit after the object's
	   start, but we also ended at the bit after the object's end.
	   It cancels out.  */
	return indx * BYTES_PER_ALLOC_BIT;

      /* The extra 1 accounts for the starting unit, before start_bit.  */
      size = (sizeof (alloc_type) * 8 - start_bit + 1) * BYTES_PER_ALLOC_BIT;

      if (size >= max_size)
	return max_size;

      alloc_word = alloc_bits[start_word++];
    }
  else
    size = BYTES_PER_ALLOC_BIT;

  while (alloc_word == 0)
    {
      size += sizeof (alloc_type) * 8 * BYTES_PER_ALLOC_BIT;
      if (size >= max_size)
	return max_size;
      alloc_word = alloc_bits[start_word++];
    }

  indx = alloc_ffs (alloc_word);
  return size + (indx - 1) * BYTES_PER_ALLOC_BIT;
}