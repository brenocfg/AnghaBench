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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_3__* dev; } ;
typedef  TYPE_4__ spi_t ;
struct TYPE_7__ {int ck_out_edge; } ;
struct TYPE_6__ {int ck_idle_edge; } ;
struct TYPE_8__ {TYPE_2__ user; TYPE_1__ pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MODE0 ; 
 int /*<<< orphan*/  SPI_MODE1 ; 
 int /*<<< orphan*/  SPI_MODE2 ; 
 int /*<<< orphan*/  SPI_MODE3 ; 

uint8_t spiGetDataMode(spi_t * spi)
{
    if(!spi) {
        return 0;
    }
    bool idleEdge = spi->dev->pin.ck_idle_edge;
    bool outEdge = spi->dev->user.ck_out_edge;
    if(idleEdge) {
        if(outEdge) {
            return SPI_MODE2;
        }
        return SPI_MODE3;
    }
    if(outEdge) {
        return SPI_MODE1;
    }
    return SPI_MODE0;
}