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
 void* __coverity_alloc__ (size_t) ; 
 int /*<<< orphan*/  __coverity_mark_as_afm_allocated__ (void*,char*) ; 
 int /*<<< orphan*/  __coverity_negative_sink__ (size_t) ; 
 int /*<<< orphan*/  __coverity_writeall0__ (void*) ; 

void *av_mallocz(size_t size) {
    int has_memory;
    __coverity_negative_sink__(size);
    if (has_memory) {
        void *ptr = __coverity_alloc__(size);
        __coverity_writeall0__(ptr);
        __coverity_mark_as_afm_allocated__(ptr, "av_free");
        return ptr;
    } else {
        return 0;
    }
}