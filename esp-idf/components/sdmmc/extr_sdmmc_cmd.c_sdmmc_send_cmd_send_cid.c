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
typedef  int /*<<< orphan*/ * sdmmc_response_t ;
struct TYPE_7__ {int flags; int datalen; int /*<<< orphan*/ * data; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_cid_t ;
struct TYPE_8__ {int /*<<< orphan*/  is_mmc; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MMC_SEND_CID ; 
 int SCF_CMD_ADTC ; 
 int SCF_CMD_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ host_is_spi (TYPE_2__*) ; 
 scalar_t__ sdmmc_decode_cid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_flip_byte_order (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sdmmc_send_cmd (TYPE_2__*,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_send_cid(sdmmc_card_t *card, sdmmc_cid_t *out_cid)
{
    assert(out_cid);
    assert(host_is_spi(card) && "SEND_CID should only be used in SPI mode");
    assert(!card->is_mmc && "MMC cards are not supported in SPI mode");
    sdmmc_response_t buf;
    sdmmc_command_t cmd = {
        .opcode = MMC_SEND_CID,
        .flags = SCF_CMD_READ | SCF_CMD_ADTC,
        .arg = 0,
        .data = &buf[0],
        .datalen = sizeof(buf)
    };
    esp_err_t err = sdmmc_send_cmd(card, &cmd);
    if (err != ESP_OK) {
        return err;
    }
    sdmmc_flip_byte_order(buf, sizeof(buf));
    return sdmmc_decode_cid(buf, out_cid);
}