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
typedef  size_t uint ;
struct dma_pub {int dummy; } ;
struct brcms_hardware {struct dma_pub** di; } ;

/* Variables and functions */
 int dma_rxreset (struct dma_pub*) ; 

__attribute__((used)) static bool wlc_dma_rxreset(struct brcms_hardware *wlc_hw, uint fifo)
{
	struct dma_pub *di = wlc_hw->di[fifo];
	return dma_rxreset(di);
}