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
struct TYPE_2__ {int /*<<< orphan*/ ** allocptr; } ;
typedef  TYPE_1__ lzma_allocator ;

/* Variables and functions */
 int MAX_LZMA_ALLOCS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void lzma_allocator_free(void* p )
{
	lzma_allocator *codec = (lzma_allocator *)(p);

	/* free our memory */
	int i;
	for (i = 0 ; i < MAX_LZMA_ALLOCS ; i++)
	{
		if (codec->allocptr[i] != NULL)
			free(codec->allocptr[i]);
	}
}