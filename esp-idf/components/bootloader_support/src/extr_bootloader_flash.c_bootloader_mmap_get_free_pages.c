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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int /*<<< orphan*/  spi_flash_mmap_get_free_pages (int /*<<< orphan*/ ) ; 

uint32_t bootloader_mmap_get_free_pages(void)
{
    return spi_flash_mmap_get_free_pages(SPI_FLASH_MMAP_DATA);
}