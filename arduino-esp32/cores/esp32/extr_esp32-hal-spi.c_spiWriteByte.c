#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_4__* dev; } ;
typedef  TYPE_5__ spi_t ;
struct TYPE_7__ {int usr; } ;
struct TYPE_9__ {scalar_t__ usr_miso_dbitlen; } ;
struct TYPE_8__ {int usr_mosi_dbitlen; } ;
struct TYPE_10__ {TYPE_1__ cmd; int /*<<< orphan*/ * data_buf; TYPE_3__ miso_dlen; TYPE_2__ mosi_dlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 

void spiWriteByte(spi_t * spi, uint8_t data)
{
    if(!spi) {
        return;
    }
    SPI_MUTEX_LOCK();
    spi->dev->mosi_dlen.usr_mosi_dbitlen = 7;
    spi->dev->miso_dlen.usr_miso_dbitlen = 0;
    spi->dev->data_buf[0] = data;
    spi->dev->cmd.usr = 1;
    while(spi->dev->cmd.usr);
    SPI_MUTEX_UNLOCK();
}