#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  spi_buf ;
typedef  int /*<<< orphan*/ * sdmmc_response_t ;
typedef  int /*<<< orphan*/  sdmmc_csd_t ;
struct TYPE_7__ {int flags; int datalen; int /*<<< orphan*/ * response; int /*<<< orphan*/ * data; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
struct TYPE_8__ {scalar_t__ is_mmc; int /*<<< orphan*/  rca; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_ARG_RCA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_SEND_CSD ; 
 int SCF_CMD_AC ; 
 int SCF_CMD_ADTC ; 
 int SCF_CMD_READ ; 
 int SCF_RSP_R1 ; 
 int SCF_RSP_R2 ; 
 int host_is_spi (TYPE_2__*) ; 
 scalar_t__ sdmmc_decode_csd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_flip_byte_order (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sdmmc_mmc_decode_csd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sdmmc_send_cmd (TYPE_2__*,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_send_csd(sdmmc_card_t* card, sdmmc_csd_t* out_csd)
{
    /* The trick with SEND_CSD is that in SPI mode, it acts as a data read
     * command, while in SD mode it is an AC command with R2 response.
     */
    sdmmc_response_t spi_buf;
    const bool is_spi = host_is_spi(card);
    sdmmc_command_t cmd = {
            .opcode = MMC_SEND_CSD,
            .arg = is_spi ? 0 : MMC_ARG_RCA(card->rca),
            .flags = is_spi ? (SCF_CMD_READ | SCF_CMD_ADTC | SCF_RSP_R1) :
                    (SCF_CMD_AC | SCF_RSP_R2),
            .data = is_spi ? &spi_buf[0] : 0,
            .datalen = is_spi ? sizeof(spi_buf) : 0,
    };
    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (err != ESP_OK) {
        return err;
    }
    uint32_t* ptr = cmd.response;
    if (is_spi) {
        sdmmc_flip_byte_order(spi_buf,  sizeof(spi_buf));
        ptr = spi_buf;
    }
    if (card->is_mmc) {
        err = sdmmc_mmc_decode_csd(cmd.response, out_csd);
    } else {
        err = sdmmc_decode_csd(ptr, out_csd);
    }
    return err;
}