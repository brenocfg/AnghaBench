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
typedef  TYPE_1__ rmt_rx_config_t ;
typedef  int /*<<< orphan*/  rmt_item32_t ;
struct TYPE_5__ {int mem_block_num; int /*<<< orphan*/  channel; TYPE_1__ rx_config; int /*<<< orphan*/  rmt_mode; int /*<<< orphan*/  clk_div; int /*<<< orphan*/  gpio_num; } ;
typedef  TYPE_2__ rmt_config_t ;

/* Variables and functions */
 int DATA_ITEM_NUM ; 
 int /*<<< orphan*/  RMT_CLK_DIV ; 
 int RMT_ITEM32_TIMEOUT_US ; 
 int /*<<< orphan*/  RMT_MODE_RX ; 
 int /*<<< orphan*/  RMT_RX_CHANNEL ; 
 int /*<<< orphan*/  RMT_RX_GPIO_NUM ; 
 int RMT_TICK_10_US ; 
 int RMT_TX_DATA_NUM ; 
 int /*<<< orphan*/  rmt_config (TYPE_2__*) ; 
 int /*<<< orphan*/  rmt_driver_install (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_init(void)
{
    rmt_rx_config_t rx_cfg = {
        .filter_en = true,
        .filter_ticks_thresh = 100,
        .idle_threshold = RMT_ITEM32_TIMEOUT_US / 10 * (RMT_TICK_10_US),
    };
    rmt_config_t rmt_rx = {
        .channel = RMT_RX_CHANNEL,
        .gpio_num = RMT_RX_GPIO_NUM,
        .clk_div = RMT_CLK_DIV,
        .mem_block_num = 1,
        .rmt_mode = RMT_MODE_RX,
        .rx_config = rx_cfg,
    };
    rmt_config(&rmt_rx);
    rmt_driver_install(rmt_rx.channel, (sizeof(rmt_item32_t) * DATA_ITEM_NUM * (RMT_TX_DATA_NUM+6)), 0);
}