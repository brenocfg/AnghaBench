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
 int /*<<< orphan*/  UNUSED_IN_RELEASE (void const*) ; 
 scalar_t__ VM_KERNEL_UNSLIDE (void const*) ; 

void *cos_kernel_unslide(const void *ptr)
{
#if (DEVELOPMENT || DEBUG)
    return (void *)(VM_KERNEL_UNSLIDE(ptr));
#else
    UNUSED_IN_RELEASE(ptr);
    return NULL;
#endif
}