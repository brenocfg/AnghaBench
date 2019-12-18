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
typedef  int /*<<< orphan*/  esp_ota_select_entry_t ;

/* Variables and functions */
 int SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  esp_partition_write (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void write_ota_data(const esp_partition_t *otadata_partition, esp_ota_select_entry_t *ota_data, int sec_id)
{
    esp_partition_write(otadata_partition, SPI_FLASH_SEC_SIZE * sec_id, &ota_data[sec_id], sizeof(esp_ota_select_entry_t));
}