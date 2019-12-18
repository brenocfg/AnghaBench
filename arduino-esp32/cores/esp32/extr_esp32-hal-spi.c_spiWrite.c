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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {TYPE_4__* dev; } ;
typedef  TYPE_5__ spi_t ;
struct TYPE_9__ {int usr; } ;
struct TYPE_8__ {scalar_t__ usr_miso_dbitlen; } ;
struct TYPE_7__ {int usr_mosi_dbitlen; } ;
struct TYPE_10__ {TYPE_3__ cmd; int /*<<< orphan*/ * data_buf; TYPE_2__ miso_dlen; TYPE_1__ mosi_dlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 

void spiWrite(spi_t * spi, const uint32_t *data, uint8_t len)
{
    if(!spi) {
        return;
    }
    int i;
    if(len > 16) {
        len = 16;
    }
    SPI_MUTEX_LOCK();
    spi->dev->mosi_dlen.usr_mosi_dbitlen = (len * 32) - 1;
    spi->dev->miso_dlen.usr_miso_dbitlen = 0;
    for(i=0; i<len; i++) {
        spi->dev->data_buf[i] = data[i];
    }
    spi->dev->cmd.usr = 1;
    while(spi->dev->cmd.usr);
    SPI_MUTEX_UNLOCK();
}