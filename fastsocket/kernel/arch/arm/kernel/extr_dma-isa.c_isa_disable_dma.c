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
typedef  int /*<<< orphan*/  dma_t ;

/* Variables and functions */
 size_t ISA_DMA_MASK ; 
 int /*<<< orphan*/ ** isa_dma_port ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isa_disable_dma(unsigned int chan, dma_t *dma)
{
	outb(chan | 4, isa_dma_port[chan][ISA_DMA_MASK]);
}