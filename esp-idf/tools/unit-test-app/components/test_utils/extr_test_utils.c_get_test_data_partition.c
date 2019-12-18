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
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_ANY ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

const esp_partition_t *get_test_data_partition(void)
{
    /* This finds "flash_test" partition defined in partition_table_unit_test_app.csv */
    const esp_partition_t *result = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
            ESP_PARTITION_SUBTYPE_ANY, "flash_test");
    TEST_ASSERT_NOT_NULL(result); /* means partition table set wrong */
    return result;
}