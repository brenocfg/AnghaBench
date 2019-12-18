#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format_if_mount_failed; int max_files; } ;
typedef  TYPE_1__ esp_vfs_fat_sdmmc_mount_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_vfs_fat_spiflash_mount (char*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_test_wl_handle ; 

__attribute__((used)) static void test_setup(void)
{
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5
    };

    TEST_ESP_OK(esp_vfs_fat_spiflash_mount("/spiflash", NULL, &mount_config, &s_test_wl_handle));
}