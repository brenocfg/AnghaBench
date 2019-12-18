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
typedef  int /*<<< orphan*/  FLAC__real ;
typedef  int FLAC__bool ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 scalar_t__ FLAC__memory_alloc_aligned (int,void**) ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

FLAC__bool FLAC__memory_alloc_aligned_real_array(size_t elements, FLAC__real **unaligned_pointer, FLAC__real **aligned_pointer)
{
	FLAC__real *pu; /* unaligned pointer */
	union { /* union needed to comply with C99 pointer aliasing rules */
		FLAC__real *pa; /* aligned pointer */
		void       *pv; /* aligned pointer alias */
	} u;

	FLAC__ASSERT(elements > 0);
	FLAC__ASSERT(0 != unaligned_pointer);
	FLAC__ASSERT(0 != aligned_pointer);
	FLAC__ASSERT(unaligned_pointer != aligned_pointer);

	if(elements > SIZE_MAX / sizeof(*pu)) /* overflow check */
		return false;

	pu = (FLAC__real*)FLAC__memory_alloc_aligned(sizeof(*pu) * elements, &u.pv);
	if(0 == pu) {
		return false;
	}
	else {
		if(*unaligned_pointer != 0)
			free(*unaligned_pointer);
		*unaligned_pointer = pu;
		*aligned_pointer = u.pa;
		return true;
	}
}