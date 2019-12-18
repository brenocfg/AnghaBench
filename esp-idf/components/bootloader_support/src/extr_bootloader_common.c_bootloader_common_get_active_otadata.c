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
 int bootloader_common_ota_select_valid (int /*<<< orphan*/ *) ; 
 int bootloader_common_select_otadata (int /*<<< orphan*/ *,int*,int) ; 

int bootloader_common_get_active_otadata(esp_ota_select_entry_t *two_otadata)
{
    if (two_otadata == NULL) {
        return -1;
    }
    bool valid_two_otadata[2];
    valid_two_otadata[0] = bootloader_common_ota_select_valid(&two_otadata[0]);
    valid_two_otadata[1] = bootloader_common_ota_select_valid(&two_otadata[1]);
    return bootloader_common_select_otadata(two_otadata, valid_two_otadata, true);
}