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
typedef  int /*<<< orphan*/  esp_partition_pos_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  secure_version; } ;
typedef  TYPE_1__ esp_app_desc_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ bootloader_common_get_partition_description (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int esp_efuse_check_secure_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_anti_rollback(const esp_partition_pos_t *partition)
{
#ifdef CONFIG_BOOTLOADER_APP_ANTI_ROLLBACK
    esp_app_desc_t app_desc;
    esp_err_t err = bootloader_common_get_partition_description(partition, &app_desc);
    return err == ESP_OK && esp_efuse_check_secure_version(app_desc.secure_version) == true;
#else
    return true;
#endif
}