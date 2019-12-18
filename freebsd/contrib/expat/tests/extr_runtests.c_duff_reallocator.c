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
 scalar_t__ REALLOC_ALWAYS_SUCCEED ; 
 void* realloc (void*,size_t) ; 
 scalar_t__ reallocation_count ; 

__attribute__((used)) static void *duff_reallocator(void *ptr, size_t size)
{
    if (reallocation_count == 0)
        return NULL;
    if (reallocation_count != REALLOC_ALWAYS_SUCCEED)
        reallocation_count--;
    return realloc(ptr, size);
}