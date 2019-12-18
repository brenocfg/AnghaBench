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
typedef  int /*<<< orphan*/  esp_ota_select_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_common_select_otadata (int /*<<< orphan*/  const*,int*,int) ; 
 int check_invalid_otadata (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int get_last_invalid_otadata(const esp_ota_select_entry_t *two_otadata)
{

    bool invalid_otadata[2];
    invalid_otadata[0] = check_invalid_otadata(&two_otadata[0]);
    invalid_otadata[1] = check_invalid_otadata(&two_otadata[1]);
    int num_invalid_otadata = bootloader_common_select_otadata(two_otadata, invalid_otadata, false);
    ESP_LOGD(TAG, "Invalid otadata[%d]", num_invalid_otadata);
    return num_invalid_otadata;
}