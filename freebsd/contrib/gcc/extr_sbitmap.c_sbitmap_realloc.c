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
struct simple_bitmap_def {int dummy; } ;
typedef  TYPE_1__* sbitmap ;
struct TYPE_5__ {unsigned int bytes; unsigned int n_bits; unsigned int size; } ;
typedef  int /*<<< orphan*/  SBITMAP_ELT_TYPE ;

/* Variables and functions */
 unsigned int SBITMAP_SET_SIZE (unsigned int) ; 
 scalar_t__ xrealloc (TYPE_1__*,unsigned int) ; 

sbitmap
sbitmap_realloc (sbitmap src, unsigned int n_elms)
{
  unsigned int bytes, size, amt;
  sbitmap bmap;

  size = SBITMAP_SET_SIZE (n_elms);
  bytes = size * sizeof (SBITMAP_ELT_TYPE);
  amt = (sizeof (struct simple_bitmap_def)
	 + bytes - sizeof (SBITMAP_ELT_TYPE));

  if (src->bytes  >= bytes)
    {
      src->n_bits = n_elms;
      return src;
    }

  bmap = (sbitmap) xrealloc (src, amt);
  bmap->n_bits = n_elms;
  bmap->size = size;
  bmap->bytes = bytes;
  return bmap;
}