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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_flash_erase_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t bootloader_flash_erase_range(uint32_t start_addr, uint32_t size)
{
    return spi_flash_erase_range(start_addr, size);
}