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
typedef  int /*<<< orphan*/  sdmmc_scr_t ;
struct TYPE_3__ {size_t datalen; size_t blklen; int flags; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 int SCF_CMD_ADTC ; 
 int SCF_CMD_READ ; 
 int SCF_RSP_R1 ; 
 int /*<<< orphan*/  SD_APP_SEND_SCR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ heap_caps_malloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ sdmmc_decode_scr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sdmmc_send_app_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_send_scr(sdmmc_card_t* card, sdmmc_scr_t *out_scr)
{
    size_t datalen = 8;
    uint32_t* buf = (uint32_t*) heap_caps_malloc(datalen, MALLOC_CAP_DMA);
    if (buf == NULL) {
        return ESP_ERR_NO_MEM;
    }
    sdmmc_command_t cmd = {
            .data = buf,
            .datalen = datalen,
            .blklen = datalen,
            .flags = SCF_CMD_ADTC | SCF_CMD_READ | SCF_RSP_R1,
            .opcode = SD_APP_SEND_SCR
    };
    esp_err_t err = sdmmc_send_app_cmd(card, &cmd);
    if (err == ESP_OK) {
        err = sdmmc_decode_scr(buf, out_scr);
    }
    free(buf);
    return err;
}