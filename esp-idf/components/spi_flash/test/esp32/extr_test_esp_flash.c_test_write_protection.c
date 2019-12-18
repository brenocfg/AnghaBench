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
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_flash_get_chip_write_protect (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  esp_flash_set_chip_write_protect (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_write_protection(esp_flash_t* chip)
{
    bool wp = true;
    esp_err_t ret = ESP_OK;
    ret = esp_flash_get_chip_write_protect(chip, &wp);
    TEST_ESP_OK(ret);

    for (int i = 0; i < 4; i ++) {
        bool wp_write = !wp;
        ret = esp_flash_set_chip_write_protect(chip, wp_write);
        TEST_ESP_OK(ret);

        bool wp_read;
        ret = esp_flash_get_chip_write_protect(chip, &wp_read);
        TEST_ESP_OK(ret);
        TEST_ASSERT(wp_read == wp_write);
        wp = wp_read;
    }
}