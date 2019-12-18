#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  read_mode; TYPE_2__* host; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* configure_host_io_mode ) (TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CMD_FASTRD ; 
 int CMD_FASTRD_DIO ; 
 int CMD_FASTRD_DUAL ; 
 int CMD_FASTRD_QIO ; 
 int CMD_FASTRD_QUAD ; 
 int CMD_READ ; 
 int /*<<< orphan*/  ESP_ERR_FLASH_NOT_INITIALISED ; 
#define  SPI_FLASH_DIO 133 
#define  SPI_FLASH_DOUT 132 
#define  SPI_FLASH_FASTRD 131 
#define  SPI_FLASH_QIO 130 
#define  SPI_FLASH_QOUT 129 
#define  SPI_FLASH_SLOWRD 128 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ; 

esp_err_t spi_flash_chip_generic_config_host_io_mode(esp_flash_t *chip)
{
    uint32_t dummy_cyclelen_base;
    uint32_t addr_bitlen;
    uint32_t read_command;

    switch (chip->read_mode) {
    case SPI_FLASH_QIO:
        //for QIO mode, the 4 bit right after the address are used for continuous mode, should be set to 0 to avoid that.
        addr_bitlen = 32;
        dummy_cyclelen_base = 4;
        read_command = CMD_FASTRD_QIO;
        break;
    case SPI_FLASH_QOUT:
        addr_bitlen = 24;
        dummy_cyclelen_base = 8;
        read_command = CMD_FASTRD_QUAD;
        break;
    case SPI_FLASH_DIO:
        //for DIO mode, the 4 bit right after the address are used for continuous mode, should be set to 0 to avoid that.
        addr_bitlen = 28;
        dummy_cyclelen_base = 2;
        read_command = CMD_FASTRD_DIO;
        break;
    case SPI_FLASH_DOUT:
        addr_bitlen = 24;
        dummy_cyclelen_base = 8;
        read_command = CMD_FASTRD_DUAL;
        break;
    case SPI_FLASH_FASTRD:
        addr_bitlen = 24;
        dummy_cyclelen_base = 8;
        read_command = CMD_FASTRD;
        break;
    case SPI_FLASH_SLOWRD:
        addr_bitlen = 24;
        dummy_cyclelen_base = 0;
        read_command = CMD_READ;
        break;
    default:
        return ESP_ERR_FLASH_NOT_INITIALISED;
    }

    return chip->host->configure_host_io_mode(chip->host, read_command, addr_bitlen, dummy_cyclelen_base,
                                                chip->read_mode);
}