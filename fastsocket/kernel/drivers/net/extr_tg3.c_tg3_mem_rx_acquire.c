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
struct tg3_napi {int /*<<< orphan*/  rx_rcb; int /*<<< orphan*/  rx_rcb_mapping; int /*<<< orphan*/  prodring; } ;
struct tg3 {unsigned int rxq_cnt; TYPE_1__* pdev; struct tg3_napi* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_RSS ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  TG3_RX_RCB_RING_BYTES (struct tg3*) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mem_rx_release (struct tg3*) ; 
 scalar_t__ tg3_rx_prodring_init (struct tg3*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tg3_mem_rx_acquire(struct tg3 *tp)
{
	unsigned int i, limit;

	limit = tp->rxq_cnt;

	/* If RSS is enabled, we need a (dummy) producer ring
	 * set on vector zero.  This is the true hw prodring.
	 */
	if (tg3_flag(tp, ENABLE_RSS))
		limit++;

	for (i = 0; i < limit; i++) {
		struct tg3_napi *tnapi = &tp->napi[i];

		if (tg3_rx_prodring_init(tp, &tnapi->prodring))
			goto err_out;

		/* If multivector RSS is enabled, vector 0
		 * does not handle rx or tx interrupts.
		 * Don't allocate any resources for it.
		 */
		if (!i && tg3_flag(tp, ENABLE_RSS))
			continue;

		tnapi->rx_rcb = dma_alloc_coherent(&tp->pdev->dev,
						   TG3_RX_RCB_RING_BYTES(tp),
						   &tnapi->rx_rcb_mapping,
						   GFP_KERNEL | __GFP_ZERO);
		if (!tnapi->rx_rcb)
			goto err_out;
	}

	return 0;

err_out:
	tg3_mem_rx_release(tp);
	return -ENOMEM;
}