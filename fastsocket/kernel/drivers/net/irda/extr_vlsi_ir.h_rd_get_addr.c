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
struct ring_descr {TYPE_1__* hw; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rd_addr; } ;

/* Variables and functions */
 int DMA_MASK_MSTRPAGE ; 
 int MSTRPAGE_VALUE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t rd_get_addr(struct ring_descr *rd)
{
	dma_addr_t	a;

	a = le32_to_cpu(rd->hw->rd_addr);
	return (a & DMA_MASK_MSTRPAGE) | (MSTRPAGE_VALUE << 24);
}