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
typedef  int kxld_addr_t ;

/* Variables and functions */
 int round_page (int) ; 
 scalar_t__ s_cross_link_enabled ; 
 int s_cross_link_page_size ; 

kxld_addr_t kxld_round_page_cross_safe(kxld_addr_t offset)
{
#if KERNEL
    return round_page(offset);
#else
    // assume s_cross_link_page_size is power of 2
    if (s_cross_link_enabled) {
        return (offset + (s_cross_link_page_size - 1)) & 
               (~(s_cross_link_page_size - 1));
    } else {
        return round_page(offset);
    }
#endif /* KERNEL */
}