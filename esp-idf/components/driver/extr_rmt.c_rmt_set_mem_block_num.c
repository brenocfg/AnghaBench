#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* conf_ch; } ;
struct TYPE_4__ {scalar_t__ mem_size; } ;
struct TYPE_5__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ RMT ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 scalar_t__ RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RMT_MEM_CNT_ERROR_STR ; 

esp_err_t rmt_set_mem_block_num(rmt_channel_t channel, uint8_t rmt_mem_num)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT_CHECK(rmt_mem_num <= RMT_CHANNEL_MAX - channel, RMT_MEM_CNT_ERROR_STR, ESP_ERR_INVALID_ARG);
    RMT.conf_ch[channel].conf0.mem_size = rmt_mem_num;
    return ESP_OK;
}