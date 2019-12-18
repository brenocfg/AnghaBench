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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RDSR ; 
 int /*<<< orphan*/  CMD_RDSR2 ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ spi_flash_common_read_qe_sr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

esp_err_t spi_flash_common_read_status_16b_rdsr_rdsr2(esp_flash_t* chip, uint32_t* out_sr)
{
    uint32_t sr, sr2;
    esp_err_t ret = spi_flash_common_read_qe_sr(chip, CMD_RDSR2, 8, &sr2);
    if (ret == ESP_OK) {
        ret = spi_flash_common_read_qe_sr(chip, CMD_RDSR, 8, &sr);
    }
    if (ret == ESP_OK) {
        *out_sr = (sr & 0xff) | ((sr2 & 0xff) << 8);
    }
    return ret;
}