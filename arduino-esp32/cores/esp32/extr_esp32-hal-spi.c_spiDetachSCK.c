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
 scalar_t__ VSPI ; 
 int /*<<< orphan*/  pinMatrixOutDetach (int,int,int) ; 
 int /*<<< orphan*/  pinMode (int,int /*<<< orphan*/ ) ; 

void spiDetachSCK(spi_t * spi, int8_t sck)
{
    if(!spi) {
        return;
    }
    if(sck < 0) {
        if(spi->num == HSPI) {
            sck = 14;
        } else if(spi->num == VSPI) {
            sck = 18;
        } else {
            sck = 6;
        }
    }
    pinMatrixOutDetach(sck, false, false);
    pinMode(sck, INPUT);
}