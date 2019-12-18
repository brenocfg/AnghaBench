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

/* Variables and functions */
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 int /*<<< orphan*/  disable_dma (int) ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int,unsigned long) ; 
 int /*<<< orphan*/  set_dma_count (int,int) ; 
 int /*<<< orphan*/  set_dma_mode (int,int) ; 

__attribute__((used)) static void program_isa_dma(int dma, int dir, unsigned long addr, int len)
{
	unsigned long flags;

	flags = claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma, dir);
	set_dma_addr(dma, addr);
	set_dma_count(dma, len);
	enable_dma(dma);
	release_dma_lock(flags);
}