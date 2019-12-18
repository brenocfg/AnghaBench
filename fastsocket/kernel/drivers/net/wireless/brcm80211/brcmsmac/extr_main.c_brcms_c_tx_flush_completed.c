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
struct brcms_c_info {TYPE_1__* hw; } ;
struct TYPE_2__ {scalar_t__* di; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  brcms_txpktpendtot (struct brcms_c_info*) ; 
 int /*<<< orphan*/  dma_kick_tx (scalar_t__) ; 

bool brcms_c_tx_flush_completed(struct brcms_c_info *wlc)
{
	int i;

	/* Kick DMA to send any pending AMPDU */
	for (i = 0; i < ARRAY_SIZE(wlc->hw->di); i++)
		if (wlc->hw->di[i])
			dma_kick_tx(wlc->hw->di[i]);

	return !brcms_txpktpendtot(wlc);
}