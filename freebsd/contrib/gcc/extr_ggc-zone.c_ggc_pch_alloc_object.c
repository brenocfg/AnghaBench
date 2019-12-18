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
struct ggc_pch_data {int* type_bases; int orig_base; long* alloc_bits; } ;
typedef  enum gt_types_enum { ____Placeholder_gt_types_enum } gt_types_enum ;
typedef  int /*<<< orphan*/  alloc_type ;

/* Variables and functions */
 int BYTES_PER_ALLOC_BIT ; 
 int pch_bucket (void*,int,int) ; 

char *
ggc_pch_alloc_object (struct ggc_pch_data *d, void *x,
		      size_t size, bool is_string,
		      enum gt_types_enum type)
{
  size_t alloc_word, alloc_bit;
  char *result;
  int bucket = pch_bucket (x, type, is_string);

  /* Record the start of the object in the allocation bitmap.  We
     can't assert that the allocation bit is previously clear, because
     strings may violate the invariant that they are at least
     BYTES_PER_ALLOC_BIT long.  This is harmless - ggc_get_size
     should not be called for strings.  */
  alloc_word = ((d->type_bases[bucket] - d->orig_base)
		/ (8 * sizeof (alloc_type) * BYTES_PER_ALLOC_BIT));
  alloc_bit = ((d->type_bases[bucket] - d->orig_base)
	       / BYTES_PER_ALLOC_BIT) % (8 * sizeof (alloc_type));
  d->alloc_bits[alloc_word] |= 1L << alloc_bit;

  /* Place the object at the current pointer for this bucket.  */
  result = (char *) d->type_bases[bucket];
  d->type_bases[bucket] += size;
  return result;
}