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
typedef  int u32 ;
struct b43_dmaring {int dummy; } ;
struct b43_dmadesc32 {int dummy; } ;

/* Variables and functions */
 int B43_DMA32_RXDPTR ; 
 int /*<<< orphan*/  B43_DMA32_RXSTATUS ; 
 int b43_dma_read (struct b43_dmaring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int op32_get_current_rxslot(struct b43_dmaring *ring)
{
	u32 val;

	val = b43_dma_read(ring, B43_DMA32_RXSTATUS);
	val &= B43_DMA32_RXDPTR;

	return (val / sizeof(struct b43_dmadesc32));
}