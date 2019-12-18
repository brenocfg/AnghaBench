#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  spi_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 
 int /*<<< orphan*/  spiTransferBitsNL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spiTransferBits(spi_t * spi, uint32_t data, uint32_t * out, uint8_t bits)
{
    if(!spi) {
        return;
    }
    SPI_MUTEX_LOCK();
    spiTransferBitsNL(spi, data, out, bits);
    SPI_MUTEX_UNLOCK();
}