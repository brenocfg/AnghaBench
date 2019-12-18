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
struct emac_priv {TYPE_1__* ndev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_CTRL_EWCTL ; 
 int /*<<< orphan*/  EMAC_CTRL_EWINTTCNT ; 
 int /*<<< orphan*/  EMAC_EMCONTROL ; 
 int /*<<< orphan*/  EMAC_FIFOCONTROL ; 
 int /*<<< orphan*/  EMAC_MACCONFIG ; 
 int /*<<< orphan*/  EMAC_MACCONTROL ; 
 int /*<<< orphan*/  EMAC_MACINTSTATMASKED ; 
 int /*<<< orphan*/  EMAC_MACINTSTATRAW ; 
 int /*<<< orphan*/  EMAC_MACINVECTOR ; 
 int /*<<< orphan*/  EMAC_MACSTATUS ; 
 int /*<<< orphan*/  EMAC_NETOCTETS ; 
 int /*<<< orphan*/  EMAC_RXALIGNCODEERRORS ; 
 int /*<<< orphan*/  EMAC_RXBCASTFRAMES ; 
 int /*<<< orphan*/  EMAC_RXCONTROL ; 
 int /*<<< orphan*/  EMAC_RXCRCERRORS ; 
 int /*<<< orphan*/  EMAC_RXDMAOVERRUNS ; 
 int /*<<< orphan*/  EMAC_RXFILTERED ; 
 int /*<<< orphan*/  EMAC_RXFRAGMENTS ; 
 int /*<<< orphan*/  EMAC_RXGOODFRAMES ; 
 int /*<<< orphan*/  EMAC_RXHDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_RXIDVER ; 
 int /*<<< orphan*/  EMAC_RXINTMASKSET ; 
 int /*<<< orphan*/  EMAC_RXINTSTATMASKED ; 
 int /*<<< orphan*/  EMAC_RXINTSTATRAW ; 
 int /*<<< orphan*/  EMAC_RXJABBER ; 
 int /*<<< orphan*/  EMAC_RXMAXLEN ; 
 int /*<<< orphan*/  EMAC_RXMBPENABLE ; 
 int /*<<< orphan*/  EMAC_RXMCASTFRAMES ; 
 int /*<<< orphan*/  EMAC_RXMOFOVERRUNS ; 
 int /*<<< orphan*/  EMAC_RXOCTETS ; 
 int /*<<< orphan*/  EMAC_RXOVERSIZED ; 
 int /*<<< orphan*/  EMAC_RXPAUSEFRAMES ; 
 int /*<<< orphan*/  EMAC_RXQOSFILTERED ; 
 int /*<<< orphan*/  EMAC_RXSOFOVERRUNS ; 
 int /*<<< orphan*/  EMAC_RXUNDERSIZED ; 
 int /*<<< orphan*/  EMAC_RXUNICASTSET ; 
 int /*<<< orphan*/  EMAC_TXBCASTFRAMES ; 
 int /*<<< orphan*/  EMAC_TXCARRIERSENSE ; 
 int /*<<< orphan*/  EMAC_TXCOLLISION ; 
 int /*<<< orphan*/  EMAC_TXCONTROL ; 
 int /*<<< orphan*/  EMAC_TXDEFERRED ; 
 int /*<<< orphan*/  EMAC_TXEXCESSIVECOLL ; 
 int /*<<< orphan*/  EMAC_TXGOODFRAMES ; 
 int /*<<< orphan*/  EMAC_TXHDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_TXIDVER ; 
 int /*<<< orphan*/  EMAC_TXINTMASKSET ; 
 int /*<<< orphan*/  EMAC_TXINTSTATMASKED ; 
 int /*<<< orphan*/  EMAC_TXINTSTATRAW ; 
 int /*<<< orphan*/  EMAC_TXLATECOLL ; 
 int /*<<< orphan*/  EMAC_TXMCASTFRAMES ; 
 int /*<<< orphan*/  EMAC_TXMULTICOLL ; 
 int /*<<< orphan*/  EMAC_TXOCTETS ; 
 int /*<<< orphan*/  EMAC_TXPAUSEFRAMES ; 
 int /*<<< orphan*/  EMAC_TXSINGLECOLL ; 
 int /*<<< orphan*/  EMAC_TXUNDERRUN ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  emac_ctrl_read (int /*<<< orphan*/ ) ; 
 scalar_t__ emac_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emac_dump_regs(struct emac_priv *priv)
{
	struct device *emac_dev = &priv->ndev->dev;

	/* Print important registers in EMAC */
	dev_info(emac_dev, "EMAC Basic registers\n");
	dev_info(emac_dev, "EMAC: EWCTL: %08X, EWINTTCNT: %08X\n",
		emac_ctrl_read(EMAC_CTRL_EWCTL),
		emac_ctrl_read(EMAC_CTRL_EWINTTCNT));
	dev_info(emac_dev, "EMAC: TXID: %08X %s, RXID: %08X %s\n",
		emac_read(EMAC_TXIDVER),
		((emac_read(EMAC_TXCONTROL)) ? "enabled" : "disabled"),
		emac_read(EMAC_RXIDVER),
		((emac_read(EMAC_RXCONTROL)) ? "enabled" : "disabled"));
	dev_info(emac_dev, "EMAC: TXIntRaw:%08X, TxIntMasked: %08X, "\
		"TxIntMasSet: %08X\n", emac_read(EMAC_TXINTSTATRAW),
		emac_read(EMAC_TXINTSTATMASKED), emac_read(EMAC_TXINTMASKSET));
	dev_info(emac_dev, "EMAC: RXIntRaw:%08X, RxIntMasked: %08X, "\
		"RxIntMasSet: %08X\n", emac_read(EMAC_RXINTSTATRAW),
		emac_read(EMAC_RXINTSTATMASKED), emac_read(EMAC_RXINTMASKSET));
	dev_info(emac_dev, "EMAC: MacIntRaw:%08X, MacIntMasked: %08X, "\
		"MacInVector=%08X\n", emac_read(EMAC_MACINTSTATRAW),
		emac_read(EMAC_MACINTSTATMASKED), emac_read(EMAC_MACINVECTOR));
	dev_info(emac_dev, "EMAC: EmuControl:%08X, FifoControl: %08X\n",
		emac_read(EMAC_EMCONTROL), emac_read(EMAC_FIFOCONTROL));
	dev_info(emac_dev, "EMAC: MBPEnable:%08X, RXUnicastSet: %08X, "\
		"RXMaxLen=%08X\n", emac_read(EMAC_RXMBPENABLE),
		emac_read(EMAC_RXUNICASTSET), emac_read(EMAC_RXMAXLEN));
	dev_info(emac_dev, "EMAC: MacControl:%08X, MacStatus: %08X, "\
		"MacConfig=%08X\n", emac_read(EMAC_MACCONTROL),
		emac_read(EMAC_MACSTATUS), emac_read(EMAC_MACCONFIG));
	dev_info(emac_dev, "EMAC: TXHDP[0]:%08X, RXHDP[0]: %08X\n",
		emac_read(EMAC_TXHDP(0)), emac_read(EMAC_RXHDP(0)));
	dev_info(emac_dev, "EMAC Statistics\n");
	dev_info(emac_dev, "EMAC: rx_good_frames:%d\n",
		emac_read(EMAC_RXGOODFRAMES));
	dev_info(emac_dev, "EMAC: rx_broadcast_frames:%d\n",
		emac_read(EMAC_RXBCASTFRAMES));
	dev_info(emac_dev, "EMAC: rx_multicast_frames:%d\n",
		emac_read(EMAC_RXMCASTFRAMES));
	dev_info(emac_dev, "EMAC: rx_pause_frames:%d\n",
		emac_read(EMAC_RXPAUSEFRAMES));
	dev_info(emac_dev, "EMAC: rx_crcerrors:%d\n",
		emac_read(EMAC_RXCRCERRORS));
	dev_info(emac_dev, "EMAC: rx_align_code_errors:%d\n",
		emac_read(EMAC_RXALIGNCODEERRORS));
	dev_info(emac_dev, "EMAC: rx_oversized_frames:%d\n",
		emac_read(EMAC_RXOVERSIZED));
	dev_info(emac_dev, "EMAC: rx_jabber_frames:%d\n",
		emac_read(EMAC_RXJABBER));
	dev_info(emac_dev, "EMAC: rx_undersized_frames:%d\n",
		emac_read(EMAC_RXUNDERSIZED));
	dev_info(emac_dev, "EMAC: rx_fragments:%d\n",
		emac_read(EMAC_RXFRAGMENTS));
	dev_info(emac_dev, "EMAC: rx_filtered_frames:%d\n",
		emac_read(EMAC_RXFILTERED));
	dev_info(emac_dev, "EMAC: rx_qos_filtered_frames:%d\n",
		emac_read(EMAC_RXQOSFILTERED));
	dev_info(emac_dev, "EMAC: rx_octets:%d\n",
		emac_read(EMAC_RXOCTETS));
	dev_info(emac_dev, "EMAC: tx_goodframes:%d\n",
		emac_read(EMAC_TXGOODFRAMES));
	dev_info(emac_dev, "EMAC: tx_bcastframes:%d\n",
		emac_read(EMAC_TXBCASTFRAMES));
	dev_info(emac_dev, "EMAC: tx_mcastframes:%d\n",
		emac_read(EMAC_TXMCASTFRAMES));
	dev_info(emac_dev, "EMAC: tx_pause_frames:%d\n",
		emac_read(EMAC_TXPAUSEFRAMES));
	dev_info(emac_dev, "EMAC: tx_deferred_frames:%d\n",
		emac_read(EMAC_TXDEFERRED));
	dev_info(emac_dev, "EMAC: tx_collision_frames:%d\n",
		emac_read(EMAC_TXCOLLISION));
	dev_info(emac_dev, "EMAC: tx_single_coll_frames:%d\n",
		emac_read(EMAC_TXSINGLECOLL));
	dev_info(emac_dev, "EMAC: tx_mult_coll_frames:%d\n",
		emac_read(EMAC_TXMULTICOLL));
	dev_info(emac_dev, "EMAC: tx_excessive_collisions:%d\n",
		emac_read(EMAC_TXEXCESSIVECOLL));
	dev_info(emac_dev, "EMAC: tx_late_collisions:%d\n",
		emac_read(EMAC_TXLATECOLL));
	dev_info(emac_dev, "EMAC: tx_underrun:%d\n",
		emac_read(EMAC_TXUNDERRUN));
	dev_info(emac_dev, "EMAC: tx_carrier_sense_errors:%d\n",
		emac_read(EMAC_TXCARRIERSENSE));
	dev_info(emac_dev, "EMAC: tx_octets:%d\n",
		emac_read(EMAC_TXOCTETS));
	dev_info(emac_dev, "EMAC: net_octets:%d\n",
		emac_read(EMAC_NETOCTETS));
	dev_info(emac_dev, "EMAC: rx_sof_overruns:%d\n",
		emac_read(EMAC_RXSOFOVERRUNS));
	dev_info(emac_dev, "EMAC: rx_mof_overruns:%d\n",
		emac_read(EMAC_RXMOFOVERRUNS));
	dev_info(emac_dev, "EMAC: rx_dma_overruns:%d\n",
		emac_read(EMAC_RXDMAOVERRUNS));
}