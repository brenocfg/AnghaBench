#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_efuse_coding_scheme_t ;
struct TYPE_5__ {int device_role; int module_version; int setting_1; int setting_2; int custom_secure_version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ device_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  get_coding_scheme () ; 
 int /*<<< orphan*/  read_device_desc_efuse_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  read_efuse_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  write_efuse_fields (TYPE_1__*,int /*<<< orphan*/ ) ; 

void app_main(void)
{
    esp_efuse_coding_scheme_t coding_scheme = get_coding_scheme();
    
    device_desc_t device_desc = { 0 };
    read_efuse_fields(&device_desc);

    ESP_LOGW(TAG, "This example does not burn any efuse in reality only virtually");
#ifdef CONFIG_EFUSE_VIRTUAL
    ESP_LOGW(TAG, "Write operations in efuse fields are performed virtually");
    if (device_desc.device_role == 0) {
        device_desc.module_version = 1;
        device_desc.device_role = 2;
        device_desc.setting_1 = 3;
        device_desc.setting_2 = 4;
        device_desc.custom_secure_version = 5;
        write_efuse_fields(&device_desc, coding_scheme);
        read_device_desc_efuse_fields(&device_desc);
    }
#else
    ESP_LOGW(TAG, "The part of the code that writes efuse fields is disabled");
#endif

    ESP_LOGI(TAG, "Done");
}