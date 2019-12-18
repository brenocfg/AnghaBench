#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_3__* dev; } ;
typedef  TYPE_4__ spi_t ;
typedef  scalar_t__ apb_change_ev_t ;
struct TYPE_6__ {int clkdiv_pre; int clkcnt_n; int /*<<< orphan*/  val; } ;
struct TYPE_5__ {scalar_t__ usr; } ;
struct TYPE_7__ {TYPE_2__ clock; TYPE_1__ cmd; } ;

/* Variables and functions */
 scalar_t__ APB_BEFORE_CHANGE ; 
 int /*<<< orphan*/  SPI_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SPI_MUTEX_UNLOCK () ; 
 int /*<<< orphan*/  spiFrequencyToClockDiv (int) ; 

__attribute__((used)) static void _on_apb_change(void * arg, apb_change_ev_t ev_type, uint32_t old_apb, uint32_t new_apb)
{
    spi_t * spi = (spi_t *)arg;
    if(ev_type == APB_BEFORE_CHANGE){
        SPI_MUTEX_LOCK();
        while(spi->dev->cmd.usr);
    } else {
        spi->dev->clock.val = spiFrequencyToClockDiv(old_apb / ((spi->dev->clock.clkdiv_pre + 1) * (spi->dev->clock.clkcnt_n + 1)));
        SPI_MUTEX_UNLOCK();
    }
}