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
typedef  int u_int ;
typedef  int kxld_addr_t ;
typedef  int address ;

/* Variables and functions */

kxld_addr_t
kxld_align_address(kxld_addr_t address, u_int align)
{
    kxld_addr_t alignment = (1 << align);
    kxld_addr_t low_bits = 0;

    if (!align) return address;

    low_bits = (address) & (alignment - 1);
    if (low_bits) {
        address += (alignment - low_bits);
    }

    return address;
}