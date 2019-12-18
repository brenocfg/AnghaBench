#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnad {int num_rxp_per_rx; int /*<<< orphan*/  rxq_depth; int /*<<< orphan*/  rx_coalescing_timeo; } ;
struct TYPE_2__ {int hash_type; int hash_mask; int /*<<< orphan*/  toeplitz_hash_key; } ;
struct bna_rx_config {int num_paths; void* vlan_strip_status; int /*<<< orphan*/  small_buff_size; int /*<<< orphan*/  q_depth; int /*<<< orphan*/  rxp_type; TYPE_1__ rss_config; void* rss_status; int /*<<< orphan*/  coalescing_timeo; int /*<<< orphan*/  rx_type; } ;

/* Variables and functions */
 int BFI_ENET_RSS_IPV4 ; 
 int BFI_ENET_RSS_IPV4_TCP ; 
 int BFI_ENET_RSS_IPV6 ; 
 int BFI_ENET_RSS_IPV6_TCP ; 
 int /*<<< orphan*/  BFI_SMALL_RXBUF_SIZE ; 
 int /*<<< orphan*/  BNA_RXP_SLR ; 
 int /*<<< orphan*/  BNA_RX_T_REGULAR ; 
 void* BNA_STATUS_T_DISABLED ; 
 void* BNA_STATUS_T_ENABLED ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnad_init_rx_config(struct bnad *bnad, struct bna_rx_config *rx_config)
{
	rx_config->rx_type = BNA_RX_T_REGULAR;
	rx_config->num_paths = bnad->num_rxp_per_rx;
	rx_config->coalescing_timeo = bnad->rx_coalescing_timeo;

	if (bnad->num_rxp_per_rx > 1) {
		rx_config->rss_status = BNA_STATUS_T_ENABLED;
		rx_config->rss_config.hash_type =
				(BFI_ENET_RSS_IPV6 |
				 BFI_ENET_RSS_IPV6_TCP |
				 BFI_ENET_RSS_IPV4 |
				 BFI_ENET_RSS_IPV4_TCP);
		rx_config->rss_config.hash_mask =
				bnad->num_rxp_per_rx - 1;
		get_random_bytes(rx_config->rss_config.toeplitz_hash_key,
			sizeof(rx_config->rss_config.toeplitz_hash_key));
	} else {
		rx_config->rss_status = BNA_STATUS_T_DISABLED;
		memset(&rx_config->rss_config, 0,
		       sizeof(rx_config->rss_config));
	}
	rx_config->rxp_type = BNA_RXP_SLR;
	rx_config->q_depth = bnad->rxq_depth;

	rx_config->small_buff_size = BFI_SMALL_RXBUF_SIZE;

	rx_config->vlan_strip_status = BNA_STATUS_T_ENABLED;
}