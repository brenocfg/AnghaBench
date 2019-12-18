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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  response; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int SCF_CMD_BCR ; 
 int SCF_RSP_R2 ; 
 int /*<<< orphan*/  SD_READ_OCR ; 
 int /*<<< orphan*/  SD_SPI_R3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_read_ocr(sdmmc_card_t *card, uint32_t *ocrp)
{
    assert(ocrp);
    sdmmc_command_t cmd = {
        .opcode = SD_READ_OCR,
        .flags = SCF_CMD_BCR | SCF_RSP_R2
    };
    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (err != ESP_OK) {
        return err;
    }
    *ocrp = SD_SPI_R3(cmd.response);
    return ESP_OK;
}