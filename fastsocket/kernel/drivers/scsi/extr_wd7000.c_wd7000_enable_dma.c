#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dma; scalar_t__ iobase; int /*<<< orphan*/  control; } ;
typedef  TYPE_1__ Adapter ;

/* Variables and functions */
 scalar_t__ ASC_CONTROL ; 
 int /*<<< orphan*/  DMA_EN ; 
 int /*<<< orphan*/  DMA_MODE_CASCADE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wd7000_enable_dma(Adapter * host)
{
	unsigned long flags;
	host->control |= DMA_EN;
	outb(host->control, host->iobase + ASC_CONTROL);

	flags = claim_dma_lock();
	set_dma_mode(host->dma, DMA_MODE_CASCADE);
	enable_dma(host->dma);
	release_dma_lock(flags);

}