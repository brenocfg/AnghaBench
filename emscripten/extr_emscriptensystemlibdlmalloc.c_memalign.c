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
 size_t MALLOC_ALIGNMENT ; 
 void* dlmalloc (size_t) ; 
 int /*<<< orphan*/  gm ; 
 void* internal_memalign (int /*<<< orphan*/ ,size_t,size_t) ; 

void* dlmemalign(size_t alignment, size_t bytes) {
    if (alignment <= MALLOC_ALIGNMENT) {
        return dlmalloc(bytes);
    }
    return internal_memalign(gm, alignment, bytes);
}