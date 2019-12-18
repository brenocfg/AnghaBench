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
struct TYPE_3__ {size_t address; size_t size; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 size_t ESP_PARTITION_TABLE_MAX_LEN ; 
 size_t ESP_PARTITION_TABLE_OFFSET ; 
 TYPE_1__* esp_ota_get_running_partition () ; 

bool esp_partition_main_flash_region_safe(size_t addr, size_t size)
{
    bool result = true;
    if (addr <= ESP_PARTITION_TABLE_OFFSET + ESP_PARTITION_TABLE_MAX_LEN) {
        return false;
    }
    const esp_partition_t *p = esp_ota_get_running_partition();
    if (addr >= p->address && addr < p->address + p->size) {
        return false;
    }
    if (addr < p->address && addr + size > p->address) {
        return false;
    }
    return result;
}