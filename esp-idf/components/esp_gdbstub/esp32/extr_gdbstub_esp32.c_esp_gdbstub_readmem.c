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
typedef  int uint32_t ;

/* Variables and functions */

int esp_gdbstub_readmem(intptr_t addr)
{
    if (addr < 0x20000000 || addr >= 0x80000000) {
        /* see cpu_configure_region_protection */
        return -1;
    }
    uint32_t val_aligned = *(uint32_t *)(addr & (~3));
    uint32_t shift = (addr & 3) * 8;
    return (val_aligned >> shift) & 0xff;
}