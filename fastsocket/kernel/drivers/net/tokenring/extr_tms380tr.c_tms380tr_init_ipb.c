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
struct TYPE_2__ {scalar_t__ SSB_Addr; scalar_t__ SCB_Addr; int /*<<< orphan*/  DMA_Abort_Thrhld; void* TX_Burst_Size; void* RX_Burst_Size; scalar_t__ Adapter_CHK_IV; scalar_t__ SCB_Clear_IV; scalar_t__ Ring_Status_IV; scalar_t__ RX_IV; scalar_t__ TX_IV; scalar_t__ CMD_Status_IV; int /*<<< orphan*/  Init_Options; } ;
struct net_local {TYPE_1__ ipb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BURST_MODE ; 
 void* BURST_SIZE ; 
 int /*<<< orphan*/  DMA_RETRIES ; 

__attribute__((used)) static void tms380tr_init_ipb(struct net_local *tp)
{
	tp->ipb.Init_Options	= BURST_MODE;
	tp->ipb.CMD_Status_IV	= 0;
	tp->ipb.TX_IV		= 0;
	tp->ipb.RX_IV		= 0;
	tp->ipb.Ring_Status_IV	= 0;
	tp->ipb.SCB_Clear_IV	= 0;
	tp->ipb.Adapter_CHK_IV	= 0;
	tp->ipb.RX_Burst_Size	= BURST_SIZE;
	tp->ipb.TX_Burst_Size	= BURST_SIZE;
	tp->ipb.DMA_Abort_Thrhld = DMA_RETRIES;
	tp->ipb.SCB_Addr	= 0;
	tp->ipb.SSB_Addr	= 0;

	return;
}