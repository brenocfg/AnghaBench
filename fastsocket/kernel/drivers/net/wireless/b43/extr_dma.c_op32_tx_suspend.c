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
struct b43_dmaring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DMA32_TXCTL ; 
 int B43_DMA32_TXSUSPEND ; 
 int b43_dma_read (struct b43_dmaring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_write (struct b43_dmaring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void op32_tx_suspend(struct b43_dmaring *ring)
{
	b43_dma_write(ring, B43_DMA32_TXCTL, b43_dma_read(ring, B43_DMA32_TXCTL)
		      | B43_DMA32_TXSUSPEND);
}