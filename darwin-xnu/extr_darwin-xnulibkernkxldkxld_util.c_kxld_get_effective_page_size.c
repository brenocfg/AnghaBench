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
typedef  int /*<<< orphan*/  kxld_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ s_cross_link_enabled ; 
 int /*<<< orphan*/  s_cross_link_page_size ; 

kxld_size_t kxld_get_effective_page_size(void)
{
#if KERNEL
    return PAGE_SIZE;
#else
    if (s_cross_link_enabled) {
        return s_cross_link_page_size;
    } else {
        return PAGE_SIZE;
    }
#endif /* KERNEL */
}