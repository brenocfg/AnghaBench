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
struct TYPE_3__ {int mosi_io_num; int sclk_io_num; } ;
typedef  TYPE_1__ spi_bus_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PULLUP_ONLY ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int,int /*<<< orphan*/ ) ; 

void slave_pull_up(const spi_bus_config_t* cfg, int spics_io_num)
{
    gpio_set_pull_mode(cfg->mosi_io_num, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(cfg->sclk_io_num, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(spics_io_num, GPIO_PULLUP_ONLY);
}