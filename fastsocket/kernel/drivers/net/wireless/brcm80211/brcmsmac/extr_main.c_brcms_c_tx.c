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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct dma_pub {scalar_t__ txavail; } ;
struct d11txh {int /*<<< orphan*/  TxFrameID; } ;
struct brcms_c_info {TYPE_2__* hw; TYPE_1__* pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; struct dma_pub** di; } ;
struct TYPE_3__ {int /*<<< orphan*/  ieee_hw; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ INVALIDFID ; 
 int /*<<< orphan*/  M_BCMC_FID ; 
 int TX_BCMC_FIFO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int brcms_ac_to_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_write_shm (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int brcms_c_txfifo (struct brcms_c_info*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  brcms_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_queue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static int brcms_c_tx(struct brcms_c_info *wlc, struct sk_buff *skb)
{
	struct dma_pub *dma;
	int fifo, ret = -ENOSPC;
	struct d11txh *txh;
	u16 frameid = INVALIDFID;

	fifo = brcms_ac_to_fifo(skb_get_queue_mapping(skb));
	dma = wlc->hw->di[fifo];
	txh = (struct d11txh *)(skb->data);

	if (dma->txavail == 0) {
		/*
		 * We sometimes get a frame from mac80211 after stopping
		 * the queues. This only ever seems to be a single frame
		 * and is seems likely to be a race. TX_HEADROOM should
		 * ensure that we have enough space to handle these stray
		 * packets, so warn if there isn't. If we're out of space
		 * in the tx ring and the tx queue isn't stopped then
		 * we've really got a bug; warn loudly if that happens.
		 */
		brcms_warn(wlc->hw->d11core,
			   "Received frame for tx with no space in DMA ring\n");
		WARN_ON(!ieee80211_queue_stopped(wlc->pub->ieee_hw,
						 skb_get_queue_mapping(skb)));
		return -ENOSPC;
	}

	/* When a BC/MC frame is being committed to the BCMC fifo
	 * via DMA (NOT PIO), update ucode or BSS info as appropriate.
	 */
	if (fifo == TX_BCMC_FIFO)
		frameid = le16_to_cpu(txh->TxFrameID);

	/* Commit BCMC sequence number in the SHM frame ID location */
	if (frameid != INVALIDFID) {
		/*
		 * To inform the ucode of the last mcast frame posted
		 * so that it can clear moredata bit
		 */
		brcms_b_write_shm(wlc->hw, M_BCMC_FID, frameid);
	}

	ret = brcms_c_txfifo(wlc, fifo, skb);
	/*
	 * The only reason for brcms_c_txfifo to fail is because
	 * there weren't any DMA descriptors, but we've already
	 * checked for that. So if it does fail yell loudly.
	 */
	WARN_ON_ONCE(ret);

	return ret;
}