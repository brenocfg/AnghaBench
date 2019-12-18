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
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  priority; int /*<<< orphan*/  num_descs; scalar_t__ dma_address; } ;
struct TYPE_4__ {int rx_mem_block_num; int tx_min_mem_block_num; int num_tx_queues; int num_ssid_profiles; void* debug_buffer_size; int /*<<< orphan*/  host_if_options; void* num_stations; } ;
struct wl1251_acx_config_memory {TYPE_3__* tx_queue_config; TYPE_2__ rx_queue_config; TYPE_1__ mem_config; } ;
struct wl1251 {int dummy; } ;
struct TYPE_6__ {int attributes; int /*<<< orphan*/  num_descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_MEM_CFG ; 
 int /*<<< orphan*/  ACX_RX_DESC_DEF ; 
 int /*<<< orphan*/  ACX_TX_DESC_DEF ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DEFAULT_NUM_STATIONS ; 
 int /*<<< orphan*/  DEFAULT_RXQ_PRIORITY ; 
 int /*<<< orphan*/  DEFAULT_RXQ_TYPE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOSTIF_PKT_RING ; 
 int MAX_TX_QUEUES ; 
 int /*<<< orphan*/  TRACE_BUFFER_MAX_SIZE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_config_memory*) ; 
 struct wl1251_acx_config_memory* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_acx_config_memory*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_mem_cfg(struct wl1251 *wl)
{
	struct wl1251_acx_config_memory *mem_conf;
	int ret, i;

	wl1251_debug(DEBUG_ACX, "acx mem cfg");

	mem_conf = kzalloc(sizeof(*mem_conf), GFP_KERNEL);
	if (!mem_conf) {
		ret = -ENOMEM;
		goto out;
	}

	/* memory config */
	mem_conf->mem_config.num_stations = cpu_to_le16(DEFAULT_NUM_STATIONS);
	mem_conf->mem_config.rx_mem_block_num = 35;
	mem_conf->mem_config.tx_min_mem_block_num = 64;
	mem_conf->mem_config.num_tx_queues = MAX_TX_QUEUES;
	mem_conf->mem_config.host_if_options = HOSTIF_PKT_RING;
	mem_conf->mem_config.num_ssid_profiles = 1;
	mem_conf->mem_config.debug_buffer_size =
		cpu_to_le16(TRACE_BUFFER_MAX_SIZE);

	/* RX queue config */
	mem_conf->rx_queue_config.dma_address = 0;
	mem_conf->rx_queue_config.num_descs = ACX_RX_DESC_DEF;
	mem_conf->rx_queue_config.priority = DEFAULT_RXQ_PRIORITY;
	mem_conf->rx_queue_config.type = DEFAULT_RXQ_TYPE;

	/* TX queue config */
	for (i = 0; i < MAX_TX_QUEUES; i++) {
		mem_conf->tx_queue_config[i].num_descs = ACX_TX_DESC_DEF;
		mem_conf->tx_queue_config[i].attributes = i;
	}

	ret = wl1251_cmd_configure(wl, ACX_MEM_CFG, mem_conf,
				   sizeof(*mem_conf));
	if (ret < 0) {
		wl1251_warning("wl1251 mem config failed: %d", ret);
		goto out;
	}

out:
	kfree(mem_conf);
	return ret;
}