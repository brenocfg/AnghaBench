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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  spi_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 
 int /*<<< orphan*/  __spiTransferBytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

void spiTransferBytes(spi_t * spi, const uint8_t * data, uint8_t * out, uint32_t size)
{
    if(!spi) {
        return;
    }
    SPI_MUTEX_LOCK();
    while(size) {
        if(size > 64) {
            __spiTransferBytes(spi, data, out, 64);
            size -= 64;
            if(data) {
                data += 64;
            }
            if(out) {
                out += 64;
            }
        } else {
            __spiTransferBytes(spi, data, out, size);
            size = 0;
        }
    }
    SPI_MUTEX_UNLOCK();
}