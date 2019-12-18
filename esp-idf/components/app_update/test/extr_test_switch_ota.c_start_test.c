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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int boot_count ; 
 int /*<<< orphan*/  erase_ota_data () ; 
 int /*<<< orphan*/  reboot_as_deep_sleep () ; 

__attribute__((used)) static void start_test(void)
{
    ESP_LOGI(TAG, "boot count 1 - reset");
    boot_count = 1;
    erase_ota_data();
    reboot_as_deep_sleep();
}