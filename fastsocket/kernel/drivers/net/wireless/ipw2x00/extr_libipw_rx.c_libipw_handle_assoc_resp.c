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
struct net_device {int dummy; } ;
struct libipw_rx_stats {scalar_t__ freq; scalar_t__ len; int /*<<< orphan*/  received_channel; } ;
struct TYPE_3__ {scalar_t__ old_param_count; scalar_t__ param_count; scalar_t__ supported; scalar_t__ active; } ;
struct libipw_network {int flags; int capability; int erp_value; int /*<<< orphan*/  stats; int /*<<< orphan*/  mode; scalar_t__ rsn_ie_len; scalar_t__ wpa_ie_len; int /*<<< orphan*/  channel; scalar_t__ ssid_len; scalar_t__ last_associate; scalar_t__ rates_ex_len; scalar_t__ rates_len; int /*<<< orphan*/  last_scanned; int /*<<< orphan*/ * bssid; void* listen_interval; void* atim_window; TYPE_1__ qos_data; int /*<<< orphan*/ * ibss_dfs; } ;
struct libipw_device {int /*<<< orphan*/  (* handle_assoc_response ) (struct net_device*,struct libipw_assoc_response*,struct libipw_network*) ;struct net_device* dev; } ;
struct TYPE_4__ {struct libipw_rx_stats* addr3; } ;
struct libipw_assoc_response {int /*<<< orphan*/  info_element; int /*<<< orphan*/  capability; TYPE_2__ header; int /*<<< orphan*/  status; int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  IEEE_A ; 
 int /*<<< orphan*/  IEEE_B ; 
 int /*<<< orphan*/  IEEE_G ; 
 scalar_t__ LIBIPW_52GHZ_BAND ; 
 int NETWORK_HAS_CCK ; 
 int NETWORK_HAS_OFDM ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  jiffies ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ libipw_parse_info_param (int /*<<< orphan*/ ,scalar_t__,struct libipw_network*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct libipw_rx_stats*,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct libipw_assoc_response*,struct libipw_network*) ; 

__attribute__((used)) static int libipw_handle_assoc_resp(struct libipw_device *ieee, struct libipw_assoc_response
				       *frame, struct libipw_rx_stats *stats)
{
	struct libipw_network network_resp = {
		.ibss_dfs = NULL,
	};
	struct libipw_network *network = &network_resp;
	struct net_device *dev = ieee->dev;

	network->flags = 0;
	network->qos_data.active = 0;
	network->qos_data.supported = 0;
	network->qos_data.param_count = 0;
	network->qos_data.old_param_count = 0;

	//network->atim_window = le16_to_cpu(frame->aid) & (0x3FFF);
	network->atim_window = le16_to_cpu(frame->aid);
	network->listen_interval = le16_to_cpu(frame->status);
	memcpy(network->bssid, frame->header.addr3, ETH_ALEN);
	network->capability = le16_to_cpu(frame->capability);
	network->last_scanned = jiffies;
	network->rates_len = network->rates_ex_len = 0;
	network->last_associate = 0;
	network->ssid_len = 0;
	network->erp_value =
	    (network->capability & WLAN_CAPABILITY_IBSS) ? 0x3 : 0x0;

	if (stats->freq == LIBIPW_52GHZ_BAND) {
		/* for A band (No DS info) */
		network->channel = stats->received_channel;
	} else
		network->flags |= NETWORK_HAS_CCK;

	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;

	if (libipw_parse_info_param
	    (frame->info_element, stats->len - sizeof(*frame), network))
		return 1;

	network->mode = 0;
	if (stats->freq == LIBIPW_52GHZ_BAND)
		network->mode = IEEE_A;
	else {
		if (network->flags & NETWORK_HAS_OFDM)
			network->mode |= IEEE_G;
		if (network->flags & NETWORK_HAS_CCK)
			network->mode |= IEEE_B;
	}

	memcpy(&network->stats, stats, sizeof(network->stats));

	if (ieee->handle_assoc_response != NULL)
		ieee->handle_assoc_response(dev, frame, network);

	return 0;
}