#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int div_factor_p; int div_factor_h; int div_factor_m; int phase_dout; int phase_din; scalar_t__ phase_core; } ;
struct TYPE_4__ {TYPE_1__ clock; } ;

/* Variables and functions */
 TYPE_2__ SDMMC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 

__attribute__((used)) static void sdmmc_host_set_clk_div(int div)
{
    // Set frequency to 160MHz / div
    // div = p + 1
    // duty cycle = (h + 1)/(p + 1) (should be = 1/2)
    assert (div > 1 && div <= 16);
    int p = div - 1;
    int h = div / 2 - 1;

    SDMMC.clock.div_factor_p = p;
    SDMMC.clock.div_factor_h = h;
    SDMMC.clock.div_factor_m = p;
    // Set phases for in/out clocks
    SDMMC.clock.phase_dout = 4;     // 180 degree phase on the output clock
    SDMMC.clock.phase_din = 4;      // 180 degree phase on the input clock
    SDMMC.clock.phase_core = 0;
    // Wait for the clock to propagate
    ets_delay_us(10);
}