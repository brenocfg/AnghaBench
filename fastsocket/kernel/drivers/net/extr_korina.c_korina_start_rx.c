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
struct korina_private {int /*<<< orphan*/  rx_dma_regs; } ;
struct dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPHYSADDR (struct dma_desc*) ; 
 int /*<<< orphan*/  korina_start_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void korina_start_rx(struct korina_private *lp,
					struct dma_desc *rd)
{
	korina_start_dma(lp->rx_dma_regs, CPHYSADDR(rd));
}