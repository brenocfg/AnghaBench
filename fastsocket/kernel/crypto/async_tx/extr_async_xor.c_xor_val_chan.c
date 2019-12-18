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
struct page {int dummy; } ;
struct dma_chan {int dummy; } ;
struct async_submit_ctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_XOR_VAL ; 
 struct dma_chan* async_tx_find_channel (struct async_submit_ctl*,int /*<<< orphan*/ ,struct page**,int,struct page**,int,size_t) ; 

__attribute__((used)) static inline struct dma_chan *
xor_val_chan(struct async_submit_ctl *submit, struct page *dest,
		 struct page **src_list, int src_cnt, size_t len)
{
	#ifdef CONFIG_ASYNC_TX_DISABLE_XOR_VAL_DMA
	return NULL;
	#endif
	return async_tx_find_channel(submit, DMA_XOR_VAL, &dest, 1, src_list,
				     src_cnt, len);
}