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
struct wl1251 {int dummy; } ;
struct TYPE_3__ {scalar_t__ status; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct acx_data_path_params_resp {TYPE_2__ header; } ;
struct acx_data_path_params {int tx_complete_threshold; int /*<<< orphan*/  tx_complete_timeout; int /*<<< orphan*/  tx_complete_ring_depth; int /*<<< orphan*/  tx_packet_ring_chunk_num; int /*<<< orphan*/  rx_packet_ring_chunk_num; int /*<<< orphan*/  tx_packet_ring_chunk_size; int /*<<< orphan*/  rx_packet_ring_chunk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_DATA_PATH_PARAMS ; 
 scalar_t__ CMD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DP_RX_PACKET_RING_CHUNK_NUM ; 
 int /*<<< orphan*/  DP_RX_PACKET_RING_CHUNK_SIZE ; 
 int /*<<< orphan*/  DP_TX_COMPLETE_TIME_OUT ; 
 int /*<<< orphan*/  DP_TX_PACKET_RING_CHUNK_NUM ; 
 int /*<<< orphan*/  DP_TX_PACKET_RING_CHUNK_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_TX_CMPLT_BLOCK_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_data_path_params*) ; 
 struct acx_data_path_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_data_path_params*,int) ; 
 int wl1251_cmd_interrogate (struct wl1251*,int /*<<< orphan*/ ,struct acx_data_path_params_resp*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,...) ; 

int wl1251_acx_data_path_params(struct wl1251 *wl,
				struct acx_data_path_params_resp *resp)
{
	struct acx_data_path_params *params;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx data path params");

	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (!params) {
		ret = -ENOMEM;
		goto out;
	}

	params->rx_packet_ring_chunk_size = DP_RX_PACKET_RING_CHUNK_SIZE;
	params->tx_packet_ring_chunk_size = DP_TX_PACKET_RING_CHUNK_SIZE;

	params->rx_packet_ring_chunk_num = DP_RX_PACKET_RING_CHUNK_NUM;
	params->tx_packet_ring_chunk_num = DP_TX_PACKET_RING_CHUNK_NUM;

	params->tx_complete_threshold = 1;

	params->tx_complete_ring_depth = FW_TX_CMPLT_BLOCK_SIZE;

	params->tx_complete_timeout = DP_TX_COMPLETE_TIME_OUT;

	ret = wl1251_cmd_configure(wl, ACX_DATA_PATH_PARAMS,
				   params, sizeof(*params));
	if (ret < 0)
		goto out;

	/* FIXME: shouldn't this be ACX_DATA_PATH_RESP_PARAMS? */
	ret = wl1251_cmd_interrogate(wl, ACX_DATA_PATH_PARAMS,
				     resp, sizeof(*resp));

	if (ret < 0) {
		wl1251_warning("failed to read data path parameters: %d", ret);
		goto out;
	} else if (resp->header.cmd.status != CMD_STATUS_SUCCESS) {
		wl1251_warning("data path parameter acx status failed");
		ret = -EIO;
		goto out;
	}

out:
	kfree(params);
	return ret;
}