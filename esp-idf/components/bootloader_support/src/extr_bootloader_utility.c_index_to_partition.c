#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
struct TYPE_6__ {int app_count; TYPE_1__* ota; TYPE_1__ test; TYPE_1__ factory; } ;
typedef  TYPE_2__ bootloader_state_t ;

/* Variables and functions */
 int FACTORY_INDEX ; 
 int MAX_OTA_SLOTS ; 
 int TEST_APP_INDEX ; 

__attribute__((used)) static esp_partition_pos_t index_to_partition(const bootloader_state_t *bs, int index)
{
    if (index == FACTORY_INDEX) {
        return bs->factory;
    }

    if (index == TEST_APP_INDEX) {
        return bs->test;
    }

    if (index >= 0 && index < MAX_OTA_SLOTS && index < bs->app_count) {
        return bs->ota[index];
    }

    esp_partition_pos_t invalid = { 0 };
    return invalid;
}