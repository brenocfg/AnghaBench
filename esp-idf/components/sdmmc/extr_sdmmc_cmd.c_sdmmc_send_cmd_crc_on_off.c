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
struct TYPE_3__ {int arg; int flags; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ sdmmc_command_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int SCF_CMD_AC ; 
 int SCF_RSP_R1 ; 
 int /*<<< orphan*/  SD_CRC_ON_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ host_is_spi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_send_cmd (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t sdmmc_send_cmd_crc_on_off(sdmmc_card_t* card, bool crc_enable)
{
    assert(host_is_spi(card) && "CRC_ON_OFF can only be used in SPI mode");
    sdmmc_command_t cmd = {
            .opcode = SD_CRC_ON_OFF,
            .arg = crc_enable ? 1 : 0,
            .flags = SCF_CMD_AC | SCF_RSP_R1
    };
    return sdmmc_send_cmd(card, &cmd);
}