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
 int EINVAL ; 
 int ENOMEM ; 
 size_t MALLOC_ALIGNMENT ; 
 size_t MAX_REQUEST ; 
 size_t MIN_CHUNK_SIZE ; 
 size_t SIZE_T_ONE ; 
 void* dlmalloc (size_t) ; 
 int /*<<< orphan*/  gm ; 
 void* internal_memalign (int /*<<< orphan*/ ,size_t,size_t) ; 

int dlposix_memalign(void** pp, size_t alignment, size_t bytes) {
    void* mem = 0;
    if (alignment == MALLOC_ALIGNMENT)
        mem = dlmalloc(bytes);
    else {
        size_t d = alignment / sizeof(void*);
        size_t r = alignment % sizeof(void*);
        if (r != 0 || d == 0 || (d & (d-SIZE_T_ONE)) != 0)
            return EINVAL;
        else if (bytes <= MAX_REQUEST - alignment) {
            if (alignment <  MIN_CHUNK_SIZE)
                alignment = MIN_CHUNK_SIZE;
            mem = internal_memalign(gm, alignment, bytes);
        }
    }
    if (mem == 0)
        return ENOMEM;
    else {
        *pp = mem;
        return 0;
    }
}