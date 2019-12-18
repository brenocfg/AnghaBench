#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tx_desc {int dummy; } ;
struct sge_txq {int size; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * sdesc; scalar_t__ cntxt_id; int /*<<< orphan*/  phys_addr; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 scalar_t__ STAT_LEN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_txq(struct adapter *adap, struct sge_txq *q)
{
	dma_free_coherent(adap->pdev_dev,
			  q->size * sizeof(struct tx_desc) + STAT_LEN,
			  q->desc, q->phys_addr);
	q->cntxt_id = 0;
	q->sdesc = NULL;
	q->desc = NULL;
}