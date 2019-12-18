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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tx_status {int status; int frameid; } ;
struct sk_buff {size_t priority; scalar_t__ data; } ;
struct scb_ampdu_tid_ini {int dummy; } ;
struct scb_ampdu {struct scb_ampdu_tid_ini* ini; } ;
struct scb {struct scb_ampdu scb_ampdu; } ;
struct ieee80211_tx_info {int dummy; } ;
struct d11txh {int /*<<< orphan*/  MacTxControlLow; } ;
struct brcms_c_info {TYPE_1__* hw; } ;
struct ampdu_info {struct brcms_c_info* wlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * di; TYPE_2__* d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_RANGE_TRANSMITTED ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int TXC_AMPDU_LAST ; 
 int TXC_AMPDU_MASK ; 
 int TXC_AMPDU_SHIFT ; 
 int TXFID_QUEUE_MASK ; 
 int TXS_V ; 
 int TX_STATUS_ACK_RCV ; 
 int bcma_read32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_ampdu_dotxstatus_complete (struct ampdu_info*,struct scb*,struct sk_buff*,struct tx_status*,int,int) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* dma_getnexttxp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frmtxstatus ; 
 int /*<<< orphan*/  frmtxstatus2 ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_brcms_txdesc (int /*<<< orphan*/ *,struct d11txh*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void
brcms_c_ampdu_dotxstatus(struct ampdu_info *ampdu, struct scb *scb,
		     struct sk_buff *p, struct tx_status *txs)
{
	struct scb_ampdu *scb_ampdu;
	struct brcms_c_info *wlc = ampdu->wlc;
	struct scb_ampdu_tid_ini *ini;
	u32 s1 = 0, s2 = 0;
	struct ieee80211_tx_info *tx_info;

	tx_info = IEEE80211_SKB_CB(p);

	/* BMAC_NOTE: For the split driver, second level txstatus comes later
	 * So if the ACK was received then wait for the second level else just
	 * call the first one
	 */
	if (txs->status & TX_STATUS_ACK_RCV) {
		u8 status_delay = 0;

		/* wait till the next 8 bytes of txstatus is available */
		s1 = bcma_read32(wlc->hw->d11core, D11REGOFFS(frmtxstatus));
		while ((s1 & TXS_V) == 0) {
			udelay(1);
			status_delay++;
			if (status_delay > 10)
				return; /* error condition */
			s1 = bcma_read32(wlc->hw->d11core,
					 D11REGOFFS(frmtxstatus));
		}

		s2 = bcma_read32(wlc->hw->d11core, D11REGOFFS(frmtxstatus2));
	}

	if (scb) {
		scb_ampdu = &scb->scb_ampdu;
		ini = &scb_ampdu->ini[p->priority];
		brcms_c_ampdu_dotxstatus_complete(ampdu, scb, p, txs, s1, s2);
	} else {
		/* loop through all pkts and free */
		u8 queue = txs->frameid & TXFID_QUEUE_MASK;
		struct d11txh *txh;
		u16 mcl;
		while (p) {
			tx_info = IEEE80211_SKB_CB(p);
			txh = (struct d11txh *) p->data;
			trace_brcms_txdesc(&wlc->hw->d11core->dev, txh,
					   sizeof(*txh));
			mcl = le16_to_cpu(txh->MacTxControlLow);
			brcmu_pkt_buf_free_skb(p);
			/* break out if last packet of ampdu */
			if (((mcl & TXC_AMPDU_MASK) >> TXC_AMPDU_SHIFT) ==
			    TXC_AMPDU_LAST)
				break;
			p = dma_getnexttxp(wlc->hw->di[queue],
					   DMA_RANGE_TRANSMITTED);
		}
	}
}