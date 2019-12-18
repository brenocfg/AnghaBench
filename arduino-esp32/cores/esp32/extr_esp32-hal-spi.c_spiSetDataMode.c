#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {TYPE_3__* dev; } ;
typedef  TYPE_4__ spi_t ;
struct TYPE_7__ {int ck_out_edge; } ;
struct TYPE_6__ {int ck_idle_edge; } ;
struct TYPE_8__ {TYPE_2__ user; TYPE_1__ pin; } ;

/* Variables and functions */
#define  SPI_MODE0 131 
#define  SPI_MODE1 130 
#define  SPI_MODE2 129 
#define  SPI_MODE3 128 
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 

void spiSetDataMode(spi_t * spi, uint8_t dataMode)
{
    if(!spi) {
        return;
    }
    SPI_MUTEX_LOCK();
    switch (dataMode) {
    case SPI_MODE1:
        spi->dev->pin.ck_idle_edge = 0;
        spi->dev->user.ck_out_edge = 1;
        break;
    case SPI_MODE2:
        spi->dev->pin.ck_idle_edge = 1;
        spi->dev->user.ck_out_edge = 1;
        break;
    case SPI_MODE3:
        spi->dev->pin.ck_idle_edge = 1;
        spi->dev->user.ck_out_edge = 0;
        break;
    case SPI_MODE0:
    default:
        spi->dev->pin.ck_idle_edge = 0;
        spi->dev->user.ck_out_edge = 0;
        break;
    }
    SPI_MUTEX_UNLOCK();
}