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
struct TYPE_4__ {int filter_en; int filter_ticks_thresh; int idle_threshold; } ;
struct TYPE_5__ {int mem_block_num; int /*<<< orphan*/  channel; TYPE_1__ rx_config; int /*<<< orphan*/  rmt_mode; int /*<<< orphan*/  clk_div; int /*<<< orphan*/  gpio_num; } ;
typedef  TYPE_2__ rmt_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  RMT_CLK_DIV ; 
 int /*<<< orphan*/  RMT_MODE_RX ; 
 int /*<<< orphan*/  RMT_RX_CHANNEL ; 
 int /*<<< orphan*/  RMT_RX_GPIO_NUM ; 
 int RMT_TICK_10_US ; 
 int /*<<< orphan*/  rmt_config (TYPE_2__*) ; 
 int /*<<< orphan*/  rmt_driver_install (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rmt_item32_tIMEOUT_US ; 

__attribute__((used)) static void nec_rx_init(void)
{
    rmt_config_t rmt_rx;
    rmt_rx.channel = RMT_RX_CHANNEL;
    rmt_rx.gpio_num = RMT_RX_GPIO_NUM;
    rmt_rx.clk_div = RMT_CLK_DIV;
    rmt_rx.mem_block_num = 1;
    rmt_rx.rmt_mode = RMT_MODE_RX;
    rmt_rx.rx_config.filter_en = true;
    rmt_rx.rx_config.filter_ticks_thresh = 100;
    rmt_rx.rx_config.idle_threshold = rmt_item32_tIMEOUT_US / 10 * (RMT_TICK_10_US);
    rmt_config(&rmt_rx);
    rmt_driver_install(rmt_rx.channel, 1000, 0);
}