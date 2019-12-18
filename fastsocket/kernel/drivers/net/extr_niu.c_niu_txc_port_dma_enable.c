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
typedef  int u64 ;
struct niu {int num_tx_rings; int /*<<< orphan*/  port; TYPE_1__* tx_rings; } ;
struct TYPE_2__ {int tx_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXC_PORT_DMA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_txc_port_dma_enable(struct niu *np, int on)
{
	u64 val = 0;

	if (on) {
		int i;

		for (i = 0; i < np->num_tx_rings; i++)
			val |= (1 << np->tx_rings[i].tx_channel);
	}
	nw64(TXC_PORT_DMA(np->port), val);
}