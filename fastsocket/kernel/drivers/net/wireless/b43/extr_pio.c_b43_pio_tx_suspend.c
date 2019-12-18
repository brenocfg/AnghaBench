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
struct TYPE_2__ {int /*<<< orphan*/  tx_queue_mcast; int /*<<< orphan*/  tx_queue_AC_VO; int /*<<< orphan*/  tx_queue_AC_VI; int /*<<< orphan*/  tx_queue_AC_BE; int /*<<< orphan*/  tx_queue_AC_BK; } ;
struct b43_wldev {TYPE_1__ pio; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PS_AWAKE ; 
 int /*<<< orphan*/  b43_pio_tx_suspend_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 

void b43_pio_tx_suspend(struct b43_wldev *dev)
{
	b43_power_saving_ctl_bits(dev, B43_PS_AWAKE);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_BK);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_BE);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_VI);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_AC_VO);
	b43_pio_tx_suspend_queue(dev->pio.tx_queue_mcast);
}