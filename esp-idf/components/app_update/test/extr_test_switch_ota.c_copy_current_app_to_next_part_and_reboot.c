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
typedef  int /*<<< orphan*/  esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  copy_current_app_to_next_part (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_ota_get_running_partition () ; 
 int /*<<< orphan*/  get_next_update_partition () ; 
 int /*<<< orphan*/  reboot_as_deep_sleep () ; 

__attribute__((used)) static void copy_current_app_to_next_part_and_reboot(void)
{
    const esp_partition_t *cur_app = esp_ota_get_running_partition();
    copy_current_app_to_next_part(cur_app, get_next_update_partition());
    reboot_as_deep_sleep();
}