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
 size_t MAX_SIZE_T ; 
 scalar_t__ calloc_must_clear (int /*<<< orphan*/ ) ; 
 void* dlmalloc (size_t) ; 
 int /*<<< orphan*/  mem2chunk (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void* dlcalloc(size_t n_elements, size_t elem_size) {
    void* mem;
    size_t req = 0;
    if (n_elements != 0) {
        req = n_elements * elem_size;
        if (((n_elements | elem_size) & ~(size_t)0xffff) &&
            (req / n_elements != elem_size))
            req = MAX_SIZE_T; /* force downstream failure on overflow */
    }
    mem = dlmalloc(req);
    if (mem != 0 && calloc_must_clear(mem2chunk(mem)))
        memset(mem, 0, req);
    return mem;
}