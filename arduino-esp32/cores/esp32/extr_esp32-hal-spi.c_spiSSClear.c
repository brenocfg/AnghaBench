#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dev; } ;
typedef  TYPE_3__ spi_t ;
struct TYPE_5__ {scalar_t__ cs_keep_active; } ;
struct TYPE_6__ {TYPE_1__ pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 

void spiSSClear(spi_t * spi)
{
    if(!spi) {
        return;
    }
    SPI_MUTEX_LOCK();
    spi->dev->pin.cs_keep_active = 0;
    SPI_MUTEX_UNLOCK();
}