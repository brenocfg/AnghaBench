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
struct sport_device {int /*<<< orphan*/  dma_tx_chan; int /*<<< orphan*/  dma_rx_chan; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcr1; int /*<<< orphan*/  tcr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPEN ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  TSPEN ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sport_stop(struct sport_device *sport)
{
	sport->regs->tcr1 &= ~TSPEN;
	sport->regs->rcr1 &= ~RSPEN;
	SSYNC();

	disable_dma(sport->dma_rx_chan);
	disable_dma(sport->dma_tx_chan);
	return 0;
}