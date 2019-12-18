#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  spics_io_num; } ;
struct TYPE_7__ {size_t id; TYPE_1__ cfg; } ;
typedef  TYPE_2__ spi_slave_t ;
struct TYPE_8__ {int /*<<< orphan*/  spics_in; } ;

/* Variables and functions */
 scalar_t__ bus_is_iomux (TYPE_2__*) ; 
 int /*<<< orphan*/  gpio_iomux_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* spi_periph_signal ; 

__attribute__((used)) static inline void restore_cs(spi_slave_t *host)
{
    if (bus_is_iomux(host)) {
        gpio_iomux_in(host->cfg.spics_io_num, spi_periph_signal[host->id].spics_in);
    } else {
        gpio_matrix_in(host->cfg.spics_io_num, spi_periph_signal[host->id].spics_in, false);
    }
}