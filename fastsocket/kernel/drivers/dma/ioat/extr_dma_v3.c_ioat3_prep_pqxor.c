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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_PREP_PQ_DISABLE_Q ; 
 struct dma_async_tx_descriptor* __ioat3_prep_pq_lock (struct dma_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned char*,size_t,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
ioat3_prep_pqxor(struct dma_chan *chan, dma_addr_t dst, dma_addr_t *src,
		 unsigned int src_cnt, size_t len, unsigned long flags)
{
	unsigned char scf[src_cnt];
	dma_addr_t pq[2];

	memset(scf, 0, src_cnt);
	pq[0] = dst;
	flags |= DMA_PREP_PQ_DISABLE_Q;
	pq[1] = dst; /* specify valid address for disabled result */

	return __ioat3_prep_pq_lock(chan, NULL, pq, src, src_cnt, scf, len,
				    flags);
}