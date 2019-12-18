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
 int /*<<< orphan*/  bytes_allocated ; 
 void* kxld_page_alloc_untracked (size_t) ; 
 int /*<<< orphan*/  num_allocations ; 
 scalar_t__ round_page (size_t) ; 

void *
kxld_page_alloc(size_t size)
{
    void * ptr = NULL;

    ptr = kxld_page_alloc_untracked(size);
#if DEBUG
    if (ptr) {
        ++num_allocations;
        bytes_allocated += round_page(size);
    }
#endif /* DEBUG */

    return ptr;
}