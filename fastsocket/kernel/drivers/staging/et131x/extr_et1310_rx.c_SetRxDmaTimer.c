#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct et131x_adapter {scalar_t__ linkspeed; TYPE_4__* regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_2__ num_pkt_done; TYPE_1__ max_pkt_time; } ;
struct TYPE_8__ {TYPE_3__ rxdma; } ;

/* Variables and functions */
 scalar_t__ TRUEPHY_SPEED_100MBPS ; 
 scalar_t__ TRUEPHY_SPEED_10MBPS ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void SetRxDmaTimer(struct et131x_adapter *etdev)
{
	/* For version B silicon, we do not use the RxDMA timer for 10 and 100
	 * Mbits/s line rates. We do not enable and RxDMA interrupt coalescing.
	 */
	if ((etdev->linkspeed == TRUEPHY_SPEED_100MBPS) ||
	    (etdev->linkspeed == TRUEPHY_SPEED_10MBPS)) {
		writel(0, &etdev->regs->rxdma.max_pkt_time.value);
		writel(1, &etdev->regs->rxdma.num_pkt_done.value);
	}
}