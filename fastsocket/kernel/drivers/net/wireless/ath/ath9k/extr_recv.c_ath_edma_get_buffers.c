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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxbuf; struct ath_rx_edma* rx_edma; } ;
struct ath_softc {TYPE_1__ rx; int /*<<< orphan*/  dev; struct ath_hw* sc_ah; } ;
struct ath_rx_status {int dummy; } ;
struct ath_rx_edma {int /*<<< orphan*/  rx_fifo; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int /*<<< orphan*/  rx_bufsize; } ;
struct ath_buf {int /*<<< orphan*/  list; int /*<<< orphan*/  bf_buf_addr; } ;
typedef  enum ath9k_rx_qtype { ____Placeholder_ath9k_rx_qtype } ath9k_rx_qtype ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 struct ath_buf* SKB_CB_ATHBUF (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_process_rxdesc_edma (struct ath_hw*,struct ath_rx_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_rx_edma_buf_link (struct ath_softc*,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath_edma_get_buffers(struct ath_softc *sc,
				 enum ath9k_rx_qtype qtype,
				 struct ath_rx_status *rs,
				 struct ath_buf **dest)
{
	struct ath_rx_edma *rx_edma = &sc->rx.rx_edma[qtype];
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct sk_buff *skb;
	struct ath_buf *bf;
	int ret;

	skb = skb_peek(&rx_edma->rx_fifo);
	if (!skb)
		return false;

	bf = SKB_CB_ATHBUF(skb);
	BUG_ON(!bf);

	dma_sync_single_for_cpu(sc->dev, bf->bf_buf_addr,
				common->rx_bufsize, DMA_FROM_DEVICE);

	ret = ath9k_hw_process_rxdesc_edma(ah, rs, skb->data);
	if (ret == -EINPROGRESS) {
		/*let device gain the buffer again*/
		dma_sync_single_for_device(sc->dev, bf->bf_buf_addr,
				common->rx_bufsize, DMA_FROM_DEVICE);
		return false;
	}

	__skb_unlink(skb, &rx_edma->rx_fifo);
	if (ret == -EINVAL) {
		/* corrupt descriptor, skip this one and the following one */
		list_add_tail(&bf->list, &sc->rx.rxbuf);
		ath_rx_edma_buf_link(sc, qtype);

		skb = skb_peek(&rx_edma->rx_fifo);
		if (skb) {
			bf = SKB_CB_ATHBUF(skb);
			BUG_ON(!bf);

			__skb_unlink(skb, &rx_edma->rx_fifo);
			list_add_tail(&bf->list, &sc->rx.rxbuf);
			ath_rx_edma_buf_link(sc, qtype);
		}

		bf = NULL;
	}

	*dest = bf;
	return true;
}