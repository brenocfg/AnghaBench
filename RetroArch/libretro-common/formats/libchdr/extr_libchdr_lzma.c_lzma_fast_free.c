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
typedef  int uint32_t ;
struct TYPE_2__ {int** allocptr; } ;
typedef  TYPE_1__ lzma_allocator ;
typedef  scalar_t__ address ;

/* Variables and functions */
 int MAX_LZMA_ALLOCS ; 

__attribute__((used)) static void lzma_fast_free(void *p, void *address)
{
	int scan;
   uint32_t *ptr;
   lzma_allocator *codec;
	if (address == NULL)
		return;

	codec = (lzma_allocator *)(p);

	/* find the hunk */
	ptr = (uint32_t *)(address) - 1;
	for (scan = 0; scan < MAX_LZMA_ALLOCS; scan++)
	{
		if (ptr == codec->allocptr[scan])
		{
			/* clear the low bit of the size to allow matches */
			*ptr &= ~1;
			return;
		}
	}
}