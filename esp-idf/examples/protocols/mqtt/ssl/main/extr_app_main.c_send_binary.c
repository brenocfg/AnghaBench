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
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_mqtt_client_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int /*<<< orphan*/  TAG ; 
 int esp_mqtt_client_publish (int /*<<< orphan*/ ,char*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* esp_ota_get_running_partition () ; 
 int /*<<< orphan*/  esp_partition_mmap (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_binary(esp_mqtt_client_handle_t client)
{
    spi_flash_mmap_handle_t out_handle;
    const void *binary_address;
    const esp_partition_t* partition = esp_ota_get_running_partition();
    esp_partition_mmap(partition, 0, partition->size, SPI_FLASH_MMAP_DATA, &binary_address, &out_handle);
    int msg_id = esp_mqtt_client_publish(client, "/topic/binary", binary_address, partition->size, 0, 0);
    ESP_LOGI(TAG, "binary sent with msg_id=%d", msg_id);
}