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
typedef  int /*<<< orphan*/  u64 ;
struct sge_port_stats {int /*<<< orphan*/  tx_need_hdrroom; int /*<<< orphan*/  vlan_insert; int /*<<< orphan*/  vlan_xtract; int /*<<< orphan*/  tx_tso; int /*<<< orphan*/  tx_cso; int /*<<< orphan*/  rx_cso_good; } ;
struct sge_intr_counts {int /*<<< orphan*/ * cmdQ_full; int /*<<< orphan*/  pkt_mismatch; int /*<<< orphan*/  pkt_too_big; int /*<<< orphan*/  freelistQ_empty; int /*<<< orphan*/  respQ_overflow; int /*<<< orphan*/  respQ_empty; int /*<<< orphan*/  unhandled_irqs; int /*<<< orphan*/  pure_rsps; int /*<<< orphan*/  rx_drops; } ;
struct net_device {size_t if_port; struct adapter* ml_priv; } ;
struct ethtool_stats {int dummy; } ;
struct espi_intr_counts {int /*<<< orphan*/  parity_err; int /*<<< orphan*/  rx_ovflw; int /*<<< orphan*/  tx_drops; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  DIP4_err; int /*<<< orphan*/  DIP2_parity_err; } ;
struct cmac_statistics {int /*<<< orphan*/  RxJumboOctetsOK; int /*<<< orphan*/  RxJumboFramesOK; int /*<<< orphan*/  RxFrameTooLongErrors; int /*<<< orphan*/  RxOutOfRangeLengthField; int /*<<< orphan*/  RxInRangeLengthErrors; int /*<<< orphan*/  RxInternalMACRcvError; int /*<<< orphan*/  RxJabberErrors; int /*<<< orphan*/  RxRuntErrors; int /*<<< orphan*/  RxSequenceErrors; int /*<<< orphan*/  RxDataErrors; int /*<<< orphan*/  RxSymbolErrors; int /*<<< orphan*/  RxAlignErrors; int /*<<< orphan*/  RxFCSErrors; int /*<<< orphan*/  RxPauseFrames; int /*<<< orphan*/  RxBroadcastFramesOK; int /*<<< orphan*/  RxMulticastFramesOK; int /*<<< orphan*/  RxUnicastFramesOK; int /*<<< orphan*/  RxOctetsBad; int /*<<< orphan*/  RxOctetsOK; int /*<<< orphan*/  TxJumboOctetsOK; int /*<<< orphan*/  TxJumboFramesOK; int /*<<< orphan*/  TxFCSErrors; int /*<<< orphan*/  TxFramesWithExcessiveDeferral; int /*<<< orphan*/  TxInternalMACXmitError; int /*<<< orphan*/  TxLengthErrors; int /*<<< orphan*/  TxUnderrun; int /*<<< orphan*/  TxFramesAbortedDueToXSCollisions; int /*<<< orphan*/  TxTotalCollisions; int /*<<< orphan*/  TxLateCollisions; int /*<<< orphan*/  TxFramesWithDeferredXmissions; int /*<<< orphan*/  TxPauseFrames; int /*<<< orphan*/  TxBroadcastFramesOK; int /*<<< orphan*/  TxMulticastFramesOK; int /*<<< orphan*/  TxUnicastFramesOK; int /*<<< orphan*/  TxOctetsBad; int /*<<< orphan*/  TxOctetsOK; } ;
struct cmac {TYPE_2__* ops; } ;
struct adapter {scalar_t__ espi; int /*<<< orphan*/  sge; TYPE_1__* port; } ;
struct TYPE_4__ {struct cmac_statistics* (* statistics_update ) (struct cmac*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct cmac* mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_STATS_UPDATE_FULL ; 
 struct cmac_statistics* stub1 (struct cmac*,int /*<<< orphan*/ ) ; 
 struct espi_intr_counts* t1_espi_get_intr_counts (scalar_t__) ; 
 struct sge_intr_counts* t1_sge_get_intr_counts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_sge_get_port_stats (int /*<<< orphan*/ ,size_t,struct sge_port_stats*) ; 

__attribute__((used)) static void get_stats(struct net_device *dev, struct ethtool_stats *stats,
		      u64 *data)
{
	struct adapter *adapter = dev->ml_priv;
	struct cmac *mac = adapter->port[dev->if_port].mac;
	const struct cmac_statistics *s;
	const struct sge_intr_counts *t;
	struct sge_port_stats ss;

	s = mac->ops->statistics_update(mac, MAC_STATS_UPDATE_FULL);
	t = t1_sge_get_intr_counts(adapter->sge);
	t1_sge_get_port_stats(adapter->sge, dev->if_port, &ss);

	*data++ = s->TxOctetsOK;
	*data++ = s->TxOctetsBad;
	*data++ = s->TxUnicastFramesOK;
	*data++ = s->TxMulticastFramesOK;
	*data++ = s->TxBroadcastFramesOK;
	*data++ = s->TxPauseFrames;
	*data++ = s->TxFramesWithDeferredXmissions;
	*data++ = s->TxLateCollisions;
	*data++ = s->TxTotalCollisions;
	*data++ = s->TxFramesAbortedDueToXSCollisions;
	*data++ = s->TxUnderrun;
	*data++ = s->TxLengthErrors;
	*data++ = s->TxInternalMACXmitError;
	*data++ = s->TxFramesWithExcessiveDeferral;
	*data++ = s->TxFCSErrors;
	*data++ = s->TxJumboFramesOK;
	*data++ = s->TxJumboOctetsOK;

	*data++ = s->RxOctetsOK;
	*data++ = s->RxOctetsBad;
	*data++ = s->RxUnicastFramesOK;
	*data++ = s->RxMulticastFramesOK;
	*data++ = s->RxBroadcastFramesOK;
	*data++ = s->RxPauseFrames;
	*data++ = s->RxFCSErrors;
	*data++ = s->RxAlignErrors;
	*data++ = s->RxSymbolErrors;
	*data++ = s->RxDataErrors;
	*data++ = s->RxSequenceErrors;
	*data++ = s->RxRuntErrors;
	*data++ = s->RxJabberErrors;
	*data++ = s->RxInternalMACRcvError;
	*data++ = s->RxInRangeLengthErrors;
	*data++ = s->RxOutOfRangeLengthField;
	*data++ = s->RxFrameTooLongErrors;
	*data++ = s->RxJumboFramesOK;
	*data++ = s->RxJumboOctetsOK;

	*data++ = ss.rx_cso_good;
	*data++ = ss.tx_cso;
	*data++ = ss.tx_tso;
	*data++ = ss.vlan_xtract;
	*data++ = ss.vlan_insert;
	*data++ = ss.tx_need_hdrroom;
	
	*data++ = t->rx_drops;
	*data++ = t->pure_rsps;
	*data++ = t->unhandled_irqs;
	*data++ = t->respQ_empty;
	*data++ = t->respQ_overflow;
	*data++ = t->freelistQ_empty;
	*data++ = t->pkt_too_big;
	*data++ = t->pkt_mismatch;
	*data++ = t->cmdQ_full[0];
	*data++ = t->cmdQ_full[1];

	if (adapter->espi) {
		const struct espi_intr_counts *e;

		e = t1_espi_get_intr_counts(adapter->espi);
		*data++ = e->DIP2_parity_err;
		*data++ = e->DIP4_err;
		*data++ = e->rx_drops;
		*data++ = e->tx_drops;
		*data++ = e->rx_ovflw;
		*data++ = e->parity_err;
	}
}