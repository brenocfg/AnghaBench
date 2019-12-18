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
 scalar_t__ map ; 
 int /*<<< orphan*/  spi_flash_munmap (scalar_t__) ; 

void bootloader_munmap(const void *mapping)
{
    if (mapping && map) {
        spi_flash_munmap(map);
    }
    map = 0;
}