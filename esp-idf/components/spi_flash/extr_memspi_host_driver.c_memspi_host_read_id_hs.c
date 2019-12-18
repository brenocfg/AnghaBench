#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int miso_len; int* miso_data; int /*<<< orphan*/  mosi_len; int /*<<< orphan*/  mosi_data; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ spi_flash_trans_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* common_command ) (TYPE_2__*,TYPE_1__*) ;} ;
typedef  TYPE_2__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RDID ; 
 int /*<<< orphan*/  ESP_EARLY_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_EARLY_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_ERR_FLASH_NO_RESPONSE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 

esp_err_t memspi_host_read_id_hs(spi_flash_host_driver_t *host, uint32_t *id)
{
    //NOTE: we do have a read id function, however it doesn't work in high freq
    spi_flash_trans_t t = {
        .command = CMD_RDID,
        .mosi_data = 0,
        .mosi_len = 0,
        .miso_len = 24
    };
    host->common_command(host, &t);
    uint32_t raw_flash_id = t.miso_data[0];
    ESP_EARLY_LOGV(TAG, "raw_chip_id: %X\n", raw_flash_id);
    if (raw_flash_id == 0xFFFFFF || raw_flash_id == 0) {
        ESP_EARLY_LOGE(TAG, "no response\n");
        return ESP_ERR_FLASH_NO_RESPONSE;
    }

    // Byte swap the flash id as it's usually written the other way around
    uint8_t mfg_id = raw_flash_id & 0xFF;
    uint16_t flash_id = (raw_flash_id >> 16) | (raw_flash_id & 0xFF00);
    *id = ((uint32_t)mfg_id << 16) | flash_id;
    ESP_EARLY_LOGV(TAG, "chip_id: %X\n", *id);
    return ESP_OK;
}