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
struct tg3_napi {int /*<<< orphan*/ * hw_status; int /*<<< orphan*/  status_mapping; } ;
struct tg3_hw_stats {int dummy; } ;
struct tg3 {int irq_cnt; int /*<<< orphan*/ * hw_stats; int /*<<< orphan*/  stats_mapping; TYPE_1__* pdev; struct tg3_napi* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TG3_HW_STATUS_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mem_rx_release (struct tg3*) ; 
 int /*<<< orphan*/  tg3_mem_tx_release (struct tg3*) ; 

__attribute__((used)) static void tg3_free_consistent(struct tg3 *tp)
{
	int i;

	for (i = 0; i < tp->irq_cnt; i++) {
		struct tg3_napi *tnapi = &tp->napi[i];

		if (tnapi->hw_status) {
			dma_free_coherent(&tp->pdev->dev, TG3_HW_STATUS_SIZE,
					  tnapi->hw_status,
					  tnapi->status_mapping);
			tnapi->hw_status = NULL;
		}
	}

	tg3_mem_rx_release(tp);
	tg3_mem_tx_release(tp);

	if (tp->hw_stats) {
		dma_free_coherent(&tp->pdev->dev, sizeof(struct tg3_hw_stats),
				  tp->hw_stats, tp->stats_mapping);
		tp->hw_stats = NULL;
	}
}