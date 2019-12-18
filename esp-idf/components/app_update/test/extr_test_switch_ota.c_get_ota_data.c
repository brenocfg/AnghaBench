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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ address; scalar_t__ size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_ota_select_entry_t ;

/* Variables and functions */
 int SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * bootloader_mmap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void get_ota_data(const esp_partition_t *otadata_partition, esp_ota_select_entry_t *ota_data_0, esp_ota_select_entry_t *ota_data_1)
{
    uint32_t offset = otadata_partition->address;
    uint32_t size   = otadata_partition->size;
    if (offset != 0) {
        const esp_ota_select_entry_t *ota_select_map;
        ota_select_map = bootloader_mmap(offset, size);
        TEST_ASSERT_NOT_EQUAL(NULL, ota_select_map);

        memcpy(ota_data_0, ota_select_map, sizeof(esp_ota_select_entry_t));
        memcpy(ota_data_1, (uint8_t *)ota_select_map + SPI_FLASH_SEC_SIZE, sizeof(esp_ota_select_entry_t));
        bootloader_munmap(ota_select_map);
    }
}