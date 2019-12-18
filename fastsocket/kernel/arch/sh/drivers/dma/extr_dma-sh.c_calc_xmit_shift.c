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
typedef  size_t u32 ;
struct dma_channel {size_t chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 size_t CHCR_TS_MASK ; 
 size_t CHCR_TS_SHIFT ; 
 size_t ctrl_inl (scalar_t__) ; 
 scalar_t__* dma_base_addr ; 
 unsigned int* ts_shift ; 

__attribute__((used)) static inline unsigned int calc_xmit_shift(struct dma_channel *chan)
{
	u32 chcr = ctrl_inl(dma_base_addr[chan->chan] + CHCR);

	return ts_shift[(chcr & CHCR_TS_MASK)>>CHCR_TS_SHIFT];
}