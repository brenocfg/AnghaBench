#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num; } ;
typedef  TYPE_1__ spi_t ;
typedef  int int8_t ;

/* Variables and functions */
 scalar_t__ HSPI ; 
 int /*<<< orphan*/  INPUT ; 
 int /*<<< orphan*/  SPI_MISO_IDX (scalar_t__) ; 
 scalar_t__ VSPI ; 
 int /*<<< orphan*/  pinMatrixInDetach (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pinMode (int,int /*<<< orphan*/ ) ; 

void spiDetachMISO(spi_t * spi, int8_t miso)
{
    if(!spi) {
        return;
    }
    if(miso < 0) {
        if(spi->num == HSPI) {
            miso = 12;
        } else if(spi->num == VSPI) {
            miso = 19;
        } else {
            miso = 7;
        }
    }
    pinMatrixInDetach(SPI_MISO_IDX(spi->num), false, false);
    pinMode(miso, INPUT);
}