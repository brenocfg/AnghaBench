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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxbuf; int /*<<< orphan*/ * rx_edma; } ;
struct ath_softc {TYPE_2__ rx; int /*<<< orphan*/  dev; struct ath_hw* sc_ah; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_hp_qdepth; int /*<<< orphan*/  rx_lp_qdepth; scalar_t__ rx_status_len; } ;
struct ath_hw {TYPE_1__ caps; } ;
struct ath_common {scalar_t__ rx_bufsize; } ;
struct ath_buf {int /*<<< orphan*/  list; scalar_t__ bf_buf_addr; struct sk_buff* bf_mpdu; } ;

/* Variables and functions */
 size_t ATH9K_RX_QUEUE_HP ; 
 size_t ATH9K_RX_QUEUE_LP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_rx_bufsize (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  ath_rx_edma_cleanup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_rx_edma_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath_rxbuf_alloc (struct ath_common*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct ath_buf* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath_rx_edma_init(struct ath_softc *sc, int nbufs)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_hw *ah = sc->sc_ah;
	struct sk_buff *skb;
	struct ath_buf *bf;
	int error = 0, i;
	u32 size;

	ath9k_hw_set_rx_bufsize(ah, common->rx_bufsize -
				    ah->caps.rx_status_len);

	ath_rx_edma_init_queue(&sc->rx.rx_edma[ATH9K_RX_QUEUE_LP],
			       ah->caps.rx_lp_qdepth);
	ath_rx_edma_init_queue(&sc->rx.rx_edma[ATH9K_RX_QUEUE_HP],
			       ah->caps.rx_hp_qdepth);

	size = sizeof(struct ath_buf) * nbufs;
	bf = devm_kzalloc(sc->dev, size, GFP_KERNEL);
	if (!bf)
		return -ENOMEM;

	INIT_LIST_HEAD(&sc->rx.rxbuf);

	for (i = 0; i < nbufs; i++, bf++) {
		skb = ath_rxbuf_alloc(common, common->rx_bufsize, GFP_KERNEL);
		if (!skb) {
			error = -ENOMEM;
			goto rx_init_fail;
		}

		memset(skb->data, 0, common->rx_bufsize);
		bf->bf_mpdu = skb;

		bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
						 common->rx_bufsize,
						 DMA_BIDIRECTIONAL);
		if (unlikely(dma_mapping_error(sc->dev,
						bf->bf_buf_addr))) {
				dev_kfree_skb_any(skb);
				bf->bf_mpdu = NULL;
				bf->bf_buf_addr = 0;
				ath_err(common,
					"dma_mapping_error() on RX init\n");
				error = -ENOMEM;
				goto rx_init_fail;
		}

		list_add_tail(&bf->list, &sc->rx.rxbuf);
	}

	return 0;

rx_init_fail:
	ath_rx_edma_cleanup(sc);
	return error;
}