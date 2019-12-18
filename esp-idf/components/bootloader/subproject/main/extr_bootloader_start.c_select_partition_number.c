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
typedef  int /*<<< orphan*/  bootloader_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int INVALID_INDEX ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  bootloader_utility_load_partition_table (int /*<<< orphan*/ *) ; 
 int selected_boot_partition (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int select_partition_number (bootloader_state_t *bs)
{
    // 1. Load partition table
    if (!bootloader_utility_load_partition_table(bs)) {
        ESP_LOGE(TAG, "load partition table error!");
        return INVALID_INDEX;
    }

    // 2. Select the number of boot partition
    return selected_boot_partition(bs);
}