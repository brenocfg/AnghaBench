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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_flash_get_size (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  esp_flash_read_id (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void test_metadata(esp_flash_t *chip)
{
    ESP_LOGI(TAG, "Testing chip %p...", chip);
    uint32_t id, size;
    TEST_ESP_OK(esp_flash_read_id(chip, &id));
    TEST_ESP_OK(esp_flash_get_size(chip, &size));
    printf("Flash ID %08x detected size %d bytes\n", id, size);
}