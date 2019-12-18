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
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_2__* dev; } ;
typedef  TYPE_3__ spi_t ;
struct TYPE_5__ {int wr_bit_order; int rd_bit_order; } ;
struct TYPE_6__ {TYPE_1__ ctrl; } ;

/* Variables and functions */

uint8_t spiGetBitOrder(spi_t * spi)
{
    if(!spi) {
        return 0;
    }
    return (spi->dev->ctrl.wr_bit_order | spi->dev->ctrl.rd_bit_order) == 0;
}