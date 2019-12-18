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
 int /*<<< orphan*/  FFMAX (size_t,size_t) ; 
 size_t FFMIN (int,int /*<<< orphan*/ ) ; 
 void* av_realloc (void*,size_t) ; 
 int max_alloc_size ; 

void *av_fast_realloc(void *ptr, unsigned int *size, size_t min_size)
{
    if (min_size <= *size)
        return ptr;

    if (min_size > max_alloc_size - 32) {
        *size = 0;
        return NULL;
    }

    min_size = FFMIN(max_alloc_size - 32, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    if (!ptr)
        min_size = 0;

    *size = min_size;

    return ptr;
}