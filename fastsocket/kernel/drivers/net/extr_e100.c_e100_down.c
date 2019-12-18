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
struct nic {int /*<<< orphan*/  netdev; int /*<<< orphan*/  watchdog; TYPE_1__* pdev; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e100_clean_cbs (struct nic*) ; 
 int /*<<< orphan*/  e100_hw_reset (struct nic*) ; 
 int /*<<< orphan*/  e100_rx_clean_list (struct nic*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_down(struct nic *nic)
{
	/* wait here for poll to complete */
	napi_disable(&nic->napi);
	netif_stop_queue(nic->netdev);
	e100_hw_reset(nic);
	free_irq(nic->pdev->irq, nic->netdev);
	del_timer_sync(&nic->watchdog);
	netif_carrier_off(nic->netdev);
	e100_clean_cbs(nic);
	e100_rx_clean_list(nic);
}