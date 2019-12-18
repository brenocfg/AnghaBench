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
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ spi_slave_hal_context_t ;

/* Variables and functions */
 int spi_ll_usr_is_done (int /*<<< orphan*/ ) ; 

bool spi_slave_hal_usr_is_done(spi_slave_hal_context_t* hal)
{
    return spi_ll_usr_is_done(hal->hw);
}