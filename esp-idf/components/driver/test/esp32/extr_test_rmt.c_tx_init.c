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
struct TYPE_4__ {int loop_en; int carrier_duty_percent; int carrier_freq_hz; int carrier_level; int idle_output_en; int /*<<< orphan*/  idle_level; int /*<<< orphan*/  carrier_en; } ;
typedef  TYPE_1__ rmt_tx_config_t ;
struct TYPE_5__ {int mem_block_num; int /*<<< orphan*/  channel; int /*<<< orphan*/  rmt_mode; TYPE_1__ tx_config; int /*<<< orphan*/  clk_div; int /*<<< orphan*/  gpio_num; } ;
typedef  TYPE_2__ rmt_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  RMT_CLK_DIV ; 
 int /*<<< orphan*/  RMT_TX_CARRIER_EN ; 
 int /*<<< orphan*/  RMT_TX_CHANNEL ; 
 int /*<<< orphan*/  RMT_TX_GPIO_NUM ; 
 int /*<<< orphan*/  rmt_config (TYPE_2__*) ; 
 int /*<<< orphan*/  rmt_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_init(void)
{
    // the sender once it send something, its frq is 38kHz, and the duty cycle is 50%
    rmt_tx_config_t tx_cfg = {
        .loop_en = false,
        .carrier_duty_percent = 50,
        .carrier_freq_hz = 38000,
        .carrier_level = 1,
        .carrier_en = RMT_TX_CARRIER_EN,
        .idle_level = 0,
        .idle_output_en = true,
    };
    rmt_config_t rmt_tx = {
        .channel = RMT_TX_CHANNEL,
        .gpio_num = RMT_TX_GPIO_NUM,
        .mem_block_num = 1,
        .clk_div = RMT_CLK_DIV,
        .tx_config = tx_cfg,
        .rmt_mode = 0,
    };
    rmt_config(&rmt_tx);
    rmt_driver_install(rmt_tx.channel, 0, 0);
}