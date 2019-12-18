#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t id; } ;
typedef  TYPE_1__ spi_slave_t ;
struct TYPE_5__ {int /*<<< orphan*/  spics_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_FUNC_IN_HIGH ; 
 int /*<<< orphan*/  gpio_matrix_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* spi_periph_signal ; 

__attribute__((used)) static void freeze_cs(spi_slave_t *host)
{
    gpio_matrix_in(GPIO_FUNC_IN_HIGH, spi_periph_signal[host->id].spics_in, false);
}