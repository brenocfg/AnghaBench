#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int** allocptr; } ;
typedef  TYPE_1__ zlib_allocator ;
typedef  scalar_t__ voidpf ;
typedef  int UINT32 ;

/* Variables and functions */
 int MAX_ZLIB_ALLOCS ; 

void zlib_fast_free(voidpf opaque, voidpf address)
{
	zlib_allocator *alloc = (zlib_allocator *)opaque;
	UINT32 *ptr = (UINT32 *)address - 1;
	int i;

	/* find the hunk */
	for (i = 0; i < MAX_ZLIB_ALLOCS; i++)
		if (ptr == alloc->allocptr[i])
		{
			/* clear the low bit of the size to allow matches */
			*ptr &= ~1;
			return;
		}
}