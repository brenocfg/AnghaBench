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
struct slab {int dummy; } ;
typedef  int /*<<< orphan*/  kmem_bufctl_t ;

/* Variables and functions */
 int CFLGS_OFF_SLAB ; 
 unsigned long PAGE_SIZE ; 
 int SLAB_LIMIT ; 
 int slab_mgmt_size (int,size_t) ; 

__attribute__((used)) static void cache_estimate(unsigned long gfporder, size_t buffer_size,
			   size_t align, int flags, size_t *left_over,
			   unsigned int *num)
{
	int nr_objs;
	size_t mgmt_size;
	size_t slab_size = PAGE_SIZE << gfporder;

	/*
	 * The slab management structure can be either off the slab or
	 * on it. For the latter case, the memory allocated for a
	 * slab is used for:
	 *
	 * - The struct slab
	 * - One kmem_bufctl_t for each object
	 * - Padding to respect alignment of @align
	 * - @buffer_size bytes for each object
	 *
	 * If the slab management structure is off the slab, then the
	 * alignment will already be calculated into the size. Because
	 * the slabs are all pages aligned, the objects will be at the
	 * correct alignment when allocated.
	 */
	if (flags & CFLGS_OFF_SLAB) {
		mgmt_size = 0;
		nr_objs = slab_size / buffer_size;

		if (nr_objs > SLAB_LIMIT)
			nr_objs = SLAB_LIMIT;
	} else {
		/*
		 * Ignore padding for the initial guess. The padding
		 * is at most @align-1 bytes, and @buffer_size is at
		 * least @align. In the worst case, this result will
		 * be one greater than the number of objects that fit
		 * into the memory allocation when taking the padding
		 * into account.
		 */
		nr_objs = (slab_size - sizeof(struct slab)) /
			  (buffer_size + sizeof(kmem_bufctl_t));

		/*
		 * This calculated number will be either the right
		 * amount, or one greater than what we want.
		 */
		if (slab_mgmt_size(nr_objs, align) + nr_objs*buffer_size
		       > slab_size)
			nr_objs--;

		if (nr_objs > SLAB_LIMIT)
			nr_objs = SLAB_LIMIT;

		mgmt_size = slab_mgmt_size(nr_objs, align);
	}
	*num = nr_objs;
	*left_over = slab_size - nr_objs*buffer_size - mgmt_size;
}