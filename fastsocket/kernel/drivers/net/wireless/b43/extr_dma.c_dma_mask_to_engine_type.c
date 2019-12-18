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
typedef  scalar_t__ u64 ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;

/* Variables and functions */
 int B43_DMA_30BIT ; 
 int B43_DMA_32BIT ; 
 int B43_DMA_64BIT ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ DMA_BIT_MASK (int) ; 

__attribute__((used)) static enum b43_dmatype dma_mask_to_engine_type(u64 dmamask)
{
	if (dmamask == DMA_BIT_MASK(30))
		return B43_DMA_30BIT;
	if (dmamask == DMA_BIT_MASK(32))
		return B43_DMA_32BIT;
	if (dmamask == DMA_BIT_MASK(64))
		return B43_DMA_64BIT;
	B43_WARN_ON(1);
	return B43_DMA_30BIT;
}