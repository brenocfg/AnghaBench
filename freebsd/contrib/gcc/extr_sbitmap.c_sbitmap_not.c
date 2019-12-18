#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int* sbitmap_ptr ;
typedef  TYPE_1__* sbitmap ;
struct TYPE_4__ {unsigned int size; unsigned int* elms; unsigned int n_bits; } ;
typedef  unsigned int SBITMAP_ELT_TYPE ;

/* Variables and functions */
 unsigned int SBITMAP_ELT_BITS ; 

void
sbitmap_not (sbitmap dst, sbitmap src)
{
  unsigned int i, n = dst->size;
  sbitmap_ptr dstp = dst->elms;
  sbitmap_ptr srcp = src->elms;
  unsigned int last_bit;

  for (i = 0; i < n; i++)
    *dstp++ = ~*srcp++;

  /* Zero all bits past n_bits, by ANDing dst with sbitmap_ones.  */
  last_bit = src->n_bits % SBITMAP_ELT_BITS;
  if (last_bit)
    dst->elms[n-1] = dst->elms[n-1]
      & ((SBITMAP_ELT_TYPE)-1 >> (SBITMAP_ELT_BITS - last_bit));
}