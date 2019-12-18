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
 int /*<<< orphan*/  esp_ota_mark_app_valid_cancel_rollback () ; 

__attribute__((used)) static void mark_app_valid(void)
{
#ifdef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
    TEST_ESP_OK(esp_ota_mark_app_valid_cancel_rollback());
#endif
}