#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int address; int size; char* label; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_DATA_FAT ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_DATA ; 
 int FLASH_ERASE_SIZE ; 
 int /*<<< orphan*/  PARTITION_NAME ; 
 int /*<<< orphan*/  esp_partition_erase_range (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void example_erase_flash(void)
{
#if RECORD_IN_FLASH_EN
    printf("Erasing flash \n");
    const esp_partition_t *data_partition = NULL;
    data_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
            ESP_PARTITION_SUBTYPE_DATA_FAT, PARTITION_NAME);
    if (data_partition != NULL) {
        printf("partiton addr: 0x%08x; size: %d; label: %s\n", data_partition->address, data_partition->size, data_partition->label);
    }
    printf("Erase size: %d Bytes\n", FLASH_ERASE_SIZE);
    ESP_ERROR_CHECK(esp_partition_erase_range(data_partition, 0, FLASH_ERASE_SIZE));
#else
    printf("Skip flash erasing...\n");
#endif
}