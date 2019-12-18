#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t rmt_channel_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_12__ {TYPE_3__* conf_ch; } ;
struct TYPE_11__ {TYPE_1__* chan; } ;
struct TYPE_10__ {scalar_t__ val; } ;
struct TYPE_8__ {int tx_stop; int mem_rd_rst; scalar_t__ tx_start; } ;
struct TYPE_9__ {TYPE_2__ conf1; } ;
struct TYPE_7__ {TYPE_4__* data32; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_6__ RMT ; 
 TYPE_5__ RMTMEM ; 
 int /*<<< orphan*/  RMT_CHANNEL_ERROR_STR ; 
 size_t RMT_CHANNEL_MAX ; 
 int /*<<< orphan*/  RMT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmt_spinlock ; 

esp_err_t rmt_tx_stop(rmt_channel_t channel)
{
    RMT_CHECK(channel < RMT_CHANNEL_MAX, RMT_CHANNEL_ERROR_STR, ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&rmt_spinlock);
#ifdef CONFIG_IDF_TARGET_ESP32
    RMTMEM.chan[channel].data32[0].val = 0;
    RMT.conf_ch[channel].conf1.tx_start = 0;
#elif defined CONFIG_IDF_TARGET_ESP32S2BETA
    RMT.conf_ch[channel].conf1.tx_stop = 1;
#endif
    RMT.conf_ch[channel].conf1.mem_rd_rst = 1;
    RMT.conf_ch[channel].conf1.mem_rd_rst = 0;
    portEXIT_CRITICAL(&rmt_spinlock);
    return ESP_OK;
}