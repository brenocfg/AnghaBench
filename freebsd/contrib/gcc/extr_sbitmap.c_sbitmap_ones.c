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
typedef  TYPE_1__* sbitmap ;
struct TYPE_3__ {unsigned int* elms; unsigned int n_bits; int size; int /*<<< orphan*/  bytes; } ;
typedef  unsigned int SBITMAP_ELT_TYPE ;

/* Variables and functions */
 unsigned int SBITMAP_ELT_BITS ; 
 int /*<<< orphan*/  memset (unsigned int*,int,int /*<<< orphan*/ ) ; 

void
sbitmap_ones (sbitmap bmap)
{
  unsigned int last_bit;

  memset (bmap->elms, -1, bmap->bytes);

  last_bit = bmap->n_bits % SBITMAP_ELT_BITS;
  if (last_bit)
    bmap->elms[bmap->size - 1]
      = (SBITMAP_ELT_TYPE)-1 >> (SBITMAP_ELT_BITS - last_bit);
}