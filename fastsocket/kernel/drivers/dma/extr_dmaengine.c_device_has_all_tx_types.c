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
struct dma_device {int /*<<< orphan*/  cap_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INTERRUPT ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEMSET ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_PQ_VAL ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int /*<<< orphan*/  DMA_XOR_VAL ; 
 int /*<<< orphan*/  dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool device_has_all_tx_types(struct dma_device *device)
{
	/* A device that satisfies this test has channels that will never cause
	 * an async_tx channel switch event as all possible operation types can
	 * be handled.
	 */
	#ifdef CONFIG_ASYNC_TX_DMA
	if (!dma_has_cap(DMA_INTERRUPT, device->cap_mask))
		return false;
	#endif

	#if defined(CONFIG_ASYNC_MEMCPY) || defined(CONFIG_ASYNC_MEMCPY_MODULE)
	if (!dma_has_cap(DMA_MEMCPY, device->cap_mask))
		return false;
	#endif

	#if defined(CONFIG_ASYNC_MEMSET) || defined(CONFIG_ASYNC_MEMSET_MODULE)
	if (!dma_has_cap(DMA_MEMSET, device->cap_mask))
		return false;
	#endif

	#if defined(CONFIG_ASYNC_XOR) || defined(CONFIG_ASYNC_XOR_MODULE)
	if (!dma_has_cap(DMA_XOR, device->cap_mask))
		return false;

	#ifndef CONFIG_ASYNC_TX_DISABLE_XOR_VAL_DMA
	if (!dma_has_cap(DMA_XOR_VAL, device->cap_mask))
		return false;
	#endif
	#endif

	#if defined(CONFIG_ASYNC_PQ) || defined(CONFIG_ASYNC_PQ_MODULE)
	if (!dma_has_cap(DMA_PQ, device->cap_mask))
		return false;

	#ifndef CONFIG_ASYNC_TX_DISABLE_PQ_VAL_DMA
	if (!dma_has_cap(DMA_PQ_VAL, device->cap_mask))
		return false;
	#endif
	#endif

	return true;
}