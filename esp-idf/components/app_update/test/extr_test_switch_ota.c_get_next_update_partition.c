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
struct TYPE_5__ {int /*<<< orphan*/  address; int /*<<< orphan*/  subtype; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 TYPE_1__* esp_ota_get_next_update_partition (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const esp_partition_t * get_next_update_partition(void)
{
    const esp_partition_t *update_partition = esp_ota_get_next_update_partition(NULL);
    TEST_ASSERT_NOT_EQUAL(NULL, update_partition);
    ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x", update_partition->subtype, update_partition->address);
    return update_partition;
}