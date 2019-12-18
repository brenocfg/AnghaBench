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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ full_duplex; scalar_t__ force_media; } ;
struct nic {int flags; scalar_t__ mac; int /*<<< orphan*/  netdev; scalar_t__ loopback; TYPE_2__ mii; int /*<<< orphan*/  adaptive_ifs; } ;
struct config {int byte_count; int rx_fifo_limit; int direct_rx_dma; int standard_tcb; int standard_stat_counter; int rx_discard_short_frames; int tx_underrun_retry; int mii_mode; int pad10; int no_source_addr_insertion; int preamble_length; int ifs; int ip_addr_hi; int pad15_1; int pad15_2; int crs_or_cdt; int fc_delay_hi; int tx_padding; int fc_priority_threshold; int pad18; int full_duplex_pin; int pad20_1; int fc_priority_location; int pad21_1; int full_duplex_force; int rx_save_bad_frames; int promiscuous_mode; int multicast_all; int magic_packet_disable; int fc_disable; int mwi_enable; int rx_long_ok; int tno_intr; int rx_d102_mode; scalar_t__ loopback; int /*<<< orphan*/  adaptive_ifs; } ;
struct TYPE_3__ {struct config config; } ;
struct cb {int /*<<< orphan*/  command; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  cb_config ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ e100_phy_supports_mii (struct nic*) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ mac_82551_10 ; 
 scalar_t__ mac_82558_D101_A4 ; 
 scalar_t__ mac_82559_D101M ; 
 int /*<<< orphan*/  memset (struct config*,int /*<<< orphan*/ ,int) ; 
 int multicast_all ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int promiscuous ; 
 int wol_magic ; 

__attribute__((used)) static void e100_configure(struct nic *nic, struct cb *cb, struct sk_buff *skb)
{
	struct config *config = &cb->u.config;
	u8 *c = (u8 *)config;

	cb->command = cpu_to_le16(cb_config);

	memset(config, 0, sizeof(struct config));

	config->byte_count = 0x16;		/* bytes in this struct */
	config->rx_fifo_limit = 0x8;		/* bytes in FIFO before DMA */
	config->direct_rx_dma = 0x1;		/* reserved */
	config->standard_tcb = 0x1;		/* 1=standard, 0=extended */
	config->standard_stat_counter = 0x1;	/* 1=standard, 0=extended */
	config->rx_discard_short_frames = 0x1;	/* 1=discard, 0=pass */
	config->tx_underrun_retry = 0x3;	/* # of underrun retries */
	if (e100_phy_supports_mii(nic))
		config->mii_mode = 1;           /* 1=MII mode, 0=i82503 mode */
	config->pad10 = 0x6;
	config->no_source_addr_insertion = 0x1;	/* 1=no, 0=yes */
	config->preamble_length = 0x2;		/* 0=1, 1=3, 2=7, 3=15 bytes */
	config->ifs = 0x6;			/* x16 = inter frame spacing */
	config->ip_addr_hi = 0xF2;		/* ARP IP filter - not used */
	config->pad15_1 = 0x1;
	config->pad15_2 = 0x1;
	config->crs_or_cdt = 0x0;		/* 0=CRS only, 1=CRS or CDT */
	config->fc_delay_hi = 0x40;		/* time delay for fc frame */
	config->tx_padding = 0x1;		/* 1=pad short frames */
	config->fc_priority_threshold = 0x7;	/* 7=priority fc disabled */
	config->pad18 = 0x1;
	config->full_duplex_pin = 0x1;		/* 1=examine FDX# pin */
	config->pad20_1 = 0x1F;
	config->fc_priority_location = 0x1;	/* 1=byte#31, 0=byte#19 */
	config->pad21_1 = 0x5;

	config->adaptive_ifs = nic->adaptive_ifs;
	config->loopback = nic->loopback;

	if (nic->mii.force_media && nic->mii.full_duplex)
		config->full_duplex_force = 0x1;	/* 1=force, 0=auto */

	if (nic->flags & promiscuous || nic->loopback) {
		config->rx_save_bad_frames = 0x1;	/* 1=save, 0=discard */
		config->rx_discard_short_frames = 0x0;	/* 1=discard, 0=save */
		config->promiscuous_mode = 0x1;		/* 1=on, 0=off */
	}

	if (nic->flags & multicast_all)
		config->multicast_all = 0x1;		/* 1=accept, 0=no */

	/* disable WoL when up */
	if (netif_running(nic->netdev) || !(nic->flags & wol_magic))
		config->magic_packet_disable = 0x1;	/* 1=off, 0=on */

	if (nic->mac >= mac_82558_D101_A4) {
		config->fc_disable = 0x1;	/* 1=Tx fc off, 0=Tx fc on */
		config->mwi_enable = 0x1;	/* 1=enable, 0=disable */
		config->standard_tcb = 0x0;	/* 1=standard, 0=extended */
		config->rx_long_ok = 0x1;	/* 1=VLANs ok, 0=standard */
		if (nic->mac >= mac_82559_D101M) {
			config->tno_intr = 0x1;		/* TCO stats enable */
			/* Enable TCO in extended config */
			if (nic->mac >= mac_82551_10) {
				config->byte_count = 0x20; /* extended bytes */
				config->rx_d102_mode = 0x1; /* GMRC for TCO */
			}
		} else {
			config->standard_stat_counter = 0x0;
		}
	}

	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "[00-07]=%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
		     c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "[08-15]=%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
		     c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);
	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "[16-23]=%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
		     c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
}