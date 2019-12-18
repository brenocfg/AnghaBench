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
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_vfs_fat_spiflash_unmount (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_wl_handle ; 

__attribute__((used)) static inline void test_spi_flash_teardown(void)
{
    TEST_ESP_OK(esp_vfs_fat_spiflash_unmount("/spiflash", test_wl_handle));
}