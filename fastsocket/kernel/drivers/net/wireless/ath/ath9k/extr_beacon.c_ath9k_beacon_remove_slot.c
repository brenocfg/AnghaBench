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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath_vif {size_t av_bslot; struct ath_buf* av_bcbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  bbuf; int /*<<< orphan*/ ** bslot; } ;
struct ath_softc {int /*<<< orphan*/  bcon_tasklet; TYPE_1__ beacon; int /*<<< orphan*/  nbcnvifs; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct ath_buf {int /*<<< orphan*/  list; scalar_t__ bf_buf_addr; struct sk_buff* bf_mpdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

void ath9k_beacon_remove_slot(struct ath_softc *sc, struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_vif *avp = (void *)vif->drv_priv;
	struct ath_buf *bf = avp->av_bcbuf;

	ath_dbg(common, CONFIG, "Removing interface at beacon slot: %d\n",
		avp->av_bslot);

	tasklet_disable(&sc->bcon_tasklet);

	if (bf && bf->bf_mpdu) {
		struct sk_buff *skb = bf->bf_mpdu;
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 skb->len, DMA_TO_DEVICE);
		dev_kfree_skb_any(skb);
		bf->bf_mpdu = NULL;
		bf->bf_buf_addr = 0;
	}

	avp->av_bcbuf = NULL;
	sc->beacon.bslot[avp->av_bslot] = NULL;
	sc->nbcnvifs--;
	list_add_tail(&bf->list, &sc->beacon.bbuf);

	tasklet_enable(&sc->bcon_tasklet);
}