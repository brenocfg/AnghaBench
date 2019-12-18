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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int flags; scalar_t__ arg; int /*<<< orphan*/  response; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_TIMEOUT ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ MMC_R4 (int /*<<< orphan*/ ) ; 
 int SCF_CMD_BCR ; 
 int SCF_RSP_R4 ; 
 int SDMMC_IO_SEND_OP_COND_DELAY_MS ; 
 scalar_t__ SD_IO_OCR_MEM_READY ; 
 int /*<<< orphan*/  SD_IO_SEND_OP_COND ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

esp_err_t sdmmc_io_send_op_cond(sdmmc_card_t* card, uint32_t ocr, uint32_t *ocrp)
{
    esp_err_t err = ESP_OK;
    sdmmc_command_t cmd = {
        .flags = SCF_CMD_BCR | SCF_RSP_R4,
        .arg = ocr,
        .opcode = SD_IO_SEND_OP_COND
    };
    for (size_t i = 0; i < 100; i++) {
        err = sdmmc_send_cmd(card, &cmd);
        if (err != ESP_OK) {
            break;
        }
        if ((MMC_R4(cmd.response) & SD_IO_OCR_MEM_READY) ||
            ocr == 0) {
            break;
        }
        err = ESP_ERR_TIMEOUT;
        vTaskDelay(SDMMC_IO_SEND_OP_COND_DELAY_MS / portTICK_PERIOD_MS);
    }
    if (err == ESP_OK && ocrp != NULL)
        *ocrp = MMC_R4(cmd.response);

    return err;
}