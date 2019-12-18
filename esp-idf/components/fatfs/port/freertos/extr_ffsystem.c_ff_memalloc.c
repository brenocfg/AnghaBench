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

/* Variables and functions */
 int MALLOC_CAP_DEFAULT ; 
 int MALLOC_CAP_INTERNAL ; 
 int MALLOC_CAP_SPIRAM ; 
 void* heap_caps_malloc_prefer (int /*<<< orphan*/ ,int,int,int) ; 
 void* malloc (unsigned int) ; 
 int /*<<< orphan*/  size ; 

void* ff_memalloc (    /* Returns pointer to the allocated memory block (null on not enough core) */
    unsigned msize     /* Number of bytes to allocate */
)
{
#ifdef CONFIG_FATFS_ALLOC_EXTRAM_FIRST
    return heap_caps_malloc_prefer(size, 2, MALLOC_CAP_DEFAULT | MALLOC_CAP_SPIRAM,
                                            MALLOC_CAP_DEFAULT | MALLOC_CAP_INTERNAL);
#else
    return malloc(msize);
#endif
}