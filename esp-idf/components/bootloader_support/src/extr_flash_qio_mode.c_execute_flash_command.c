#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct TYPE_15__ {void* val; } ;
struct TYPE_14__ {int usr; } ;
struct TYPE_13__ {scalar_t__ usr_dummy_cyclelen; } ;
struct TYPE_12__ {int usr_dummy; int usr_command; int usr_miso; int usr_mosi; scalar_t__ usr_addr; } ;
struct TYPE_11__ {scalar_t__ usr_mosi_bit_len; scalar_t__ usr_mosi_dbitlen; } ;
struct TYPE_10__ {scalar_t__ usr_miso_bit_len; scalar_t__ usr_miso_dbitlen; } ;
struct TYPE_9__ {int usr_command_bitlen; scalar_t__ usr_command_value; } ;
struct TYPE_16__ {void** data_buf; TYPE_7__ ctrl; TYPE_6__ cmd; TYPE_5__ user1; TYPE_4__ user; TYPE_3__ mosi_dlen; TYPE_2__ miso_dlen; TYPE_1__ user2; } ;

/* Variables and functions */
 TYPE_8__ SPIFLASH ; 
 void* SPI_MEM_WP_REG_M ; 
 void* SPI_WP_REG_M ; 
 scalar_t__* g_rom_spiflash_dummy_len_plus ; 

__attribute__((used)) static uint32_t execute_flash_command(uint8_t command, uint32_t mosi_data, uint8_t mosi_len, uint8_t miso_len)
{
    uint32_t old_ctrl_reg = SPIFLASH.ctrl.val;
#if CONFIG_IDF_TARGET_ESP32
    SPIFLASH.ctrl.val = SPI_WP_REG_M; // keep WP high while idle, otherwise leave DIO mode
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SPIFLASH.ctrl.val = SPI_MEM_WP_REG_M; // keep WP high while idle, otherwise leave DIO mode
#endif
    SPIFLASH.user.usr_dummy = 0;
    SPIFLASH.user.usr_addr = 0;
    SPIFLASH.user.usr_command = 1;
    SPIFLASH.user2.usr_command_bitlen = 7;

    SPIFLASH.user2.usr_command_value = command;
    SPIFLASH.user.usr_miso = miso_len > 0;
#if CONFIG_IDF_TARGET_ESP32
    SPIFLASH.miso_dlen.usr_miso_dbitlen = miso_len ? (miso_len - 1) : 0;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SPIFLASH.miso_dlen.usr_miso_bit_len = miso_len ? (miso_len - 1) : 0;
#endif
    SPIFLASH.user.usr_mosi = mosi_len > 0;
#if CONFIG_IDF_TARGET_ESP32
    SPIFLASH.mosi_dlen.usr_mosi_dbitlen = mosi_len ? (mosi_len - 1) : 0;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SPIFLASH.mosi_dlen.usr_mosi_bit_len = mosi_len ? (mosi_len - 1) : 0;
#endif
    SPIFLASH.data_buf[0] = mosi_data;

    if (g_rom_spiflash_dummy_len_plus[1]) {
        /* When flash pins are mapped via GPIO matrix, need a dummy cycle before reading via MISO */
        if (miso_len > 0) {
            SPIFLASH.user.usr_dummy = 1;
            SPIFLASH.user1.usr_dummy_cyclelen = g_rom_spiflash_dummy_len_plus[1] - 1;
        } else {
            SPIFLASH.user.usr_dummy = 0;
            SPIFLASH.user1.usr_dummy_cyclelen = 0;
        }
    }

    SPIFLASH.cmd.usr = 1;
    while (SPIFLASH.cmd.usr != 0) {
    }

    SPIFLASH.ctrl.val = old_ctrl_reg;
    return SPIFLASH.data_buf[0];
}