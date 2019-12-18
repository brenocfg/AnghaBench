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
struct simple_bitmap_def {int dummy; } ;
typedef  TYPE_1__* sbitmap ;
struct TYPE_4__ {unsigned int n_bits; unsigned int size; unsigned int bytes; } ;
typedef  int /*<<< orphan*/  SBITMAP_ELT_TYPE ;

/* Variables and functions */
 unsigned int SBITMAP_SET_SIZE (unsigned int) ; 
 TYPE_1__** xmalloc (unsigned int) ; 

sbitmap *
sbitmap_vector_alloc (unsigned int n_vecs, unsigned int n_elms)
{
  unsigned int i, bytes, offset, elm_bytes, size, amt, vector_bytes;
  sbitmap *bitmap_vector;

  size = SBITMAP_SET_SIZE (n_elms);
  bytes = size * sizeof (SBITMAP_ELT_TYPE);
  elm_bytes = (sizeof (struct simple_bitmap_def)
	       + bytes - sizeof (SBITMAP_ELT_TYPE));
  vector_bytes = n_vecs * sizeof (sbitmap *);

  /* Round up `vector_bytes' to account for the alignment requirements
     of an sbitmap.  One could allocate the vector-table and set of sbitmaps
     separately, but that requires maintaining two pointers or creating
     a cover struct to hold both pointers (so our result is still just
     one pointer).  Neither is a bad idea, but this is simpler for now.  */
  {
    /* Based on DEFAULT_ALIGNMENT computation in obstack.c.  */
    struct { char x; SBITMAP_ELT_TYPE y; } align;
    int alignment = (char *) & align.y - & align.x;
    vector_bytes = (vector_bytes + alignment - 1) & ~ (alignment - 1);
  }

  amt = vector_bytes + (n_vecs * elm_bytes);
  bitmap_vector = xmalloc (amt);

  for (i = 0, offset = vector_bytes; i < n_vecs; i++, offset += elm_bytes)
    {
      sbitmap b = (sbitmap) ((char *) bitmap_vector + offset);

      bitmap_vector[i] = b;
      b->n_bits = n_elms;
      b->size = size;
      b->bytes = bytes;
    }

  return bitmap_vector;
}