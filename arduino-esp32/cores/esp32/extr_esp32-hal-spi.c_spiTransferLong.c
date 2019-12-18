#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {TYPE_5__* dev; } ;
typedef  TYPE_6__ spi_t ;
struct TYPE_11__ {int /*<<< orphan*/  rd_bit_order; int /*<<< orphan*/  wr_bit_order; } ;
struct TYPE_10__ {int usr; } ;
struct TYPE_9__ {int usr_miso_dbitlen; } ;
struct TYPE_8__ {int usr_mosi_dbitlen; } ;
struct TYPE_12__ {TYPE_4__ ctrl; int /*<<< orphan*/ * data_buf; TYPE_3__ cmd; TYPE_2__ miso_dlen; TYPE_1__ mosi_dlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 
 int /*<<< orphan*/  __spiTranslate32 (int /*<<< orphan*/ ) ; 

uint32_t spiTransferLong(spi_t * spi, uint32_t data)
{
    if(!spi) {
        return 0;
    }
    if(!spi->dev->ctrl.wr_bit_order){
        data = __spiTranslate32(data);
    }
    SPI_MUTEX_LOCK();
    spi->dev->mosi_dlen.usr_mosi_dbitlen = 31;
    spi->dev->miso_dlen.usr_miso_dbitlen = 31;
    spi->dev->data_buf[0] = data;
    spi->dev->cmd.usr = 1;
    while(spi->dev->cmd.usr);
    data = spi->dev->data_buf[0];
    SPI_MUTEX_UNLOCK();
    if(!spi->dev->ctrl.rd_bit_order){
        data = __spiTranslate32(data);
    }
    return data;
}