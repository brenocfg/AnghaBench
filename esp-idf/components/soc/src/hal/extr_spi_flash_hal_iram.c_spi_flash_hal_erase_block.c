#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll_cmd_done ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;

/* Variables and functions */
 int ADDRESS_MASK_24BIT ; 
 int /*<<< orphan*/ * get_spi_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_flash_ll_erase_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_ll_set_addr_bitlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_flash_ll_set_address (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void spi_flash_hal_erase_block(spi_flash_host_driver_t *host, uint32_t start_address)
{
    spi_dev_t *dev = get_spi_dev(host);
    spi_flash_ll_set_addr_bitlen(dev, 24);
    spi_flash_ll_set_address(dev, start_address & ADDRESS_MASK_24BIT);
    spi_flash_ll_erase_block(dev);
    host->poll_cmd_done(host);
}