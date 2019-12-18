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
struct tg3_tx_ring_info {int dummy; } ;
struct tg3_napi {int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  tx_desc_mapping; int /*<<< orphan*/  tx_buffers; } ;
struct tg3 {int txq_cnt; TYPE_1__* pdev; struct tg3_napi* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_TSS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TG3_TX_RING_BYTES ; 
 int TG3_TX_RING_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mem_tx_release (struct tg3*) ; 

__attribute__((used)) static int tg3_mem_tx_acquire(struct tg3 *tp)
{
	int i;
	struct tg3_napi *tnapi = &tp->napi[0];

	/* If multivector TSS is enabled, vector 0 does not handle
	 * tx interrupts.  Don't allocate any resources for it.
	 */
	if (tg3_flag(tp, ENABLE_TSS))
		tnapi++;

	for (i = 0; i < tp->txq_cnt; i++, tnapi++) {
		tnapi->tx_buffers = kzalloc(sizeof(struct tg3_tx_ring_info) *
					    TG3_TX_RING_SIZE, GFP_KERNEL);
		if (!tnapi->tx_buffers)
			goto err_out;

		tnapi->tx_ring = dma_alloc_coherent(&tp->pdev->dev,
						    TG3_TX_RING_BYTES,
						    &tnapi->tx_desc_mapping,
						    GFP_KERNEL);
		if (!tnapi->tx_ring)
			goto err_out;
	}

	return 0;

err_out:
	tg3_mem_tx_release(tp);
	return -ENOMEM;
}