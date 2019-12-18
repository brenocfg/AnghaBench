#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {int /*<<< orphan*/  rfkill_poll; } ;
struct il_priv {int /*<<< orphan*/  irq_tasklet; TYPE_2__ watchdog; TYPE_1__ _3945; int /*<<< orphan*/  alive_start; int /*<<< orphan*/  init_alive_start; int /*<<< orphan*/  rx_replenish; int /*<<< orphan*/  restart; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_bg_alive_start ; 
 int /*<<< orphan*/  il3945_bg_init_alive_start ; 
 int /*<<< orphan*/  il3945_bg_restart ; 
 int /*<<< orphan*/  il3945_bg_rx_replenish ; 
 int /*<<< orphan*/  il3945_hw_setup_deferred_work (struct il_priv*) ; 
 scalar_t__ il3945_irq_tasklet ; 
 int /*<<< orphan*/  il3945_rfkill_poll ; 
 int /*<<< orphan*/  il_bg_watchdog ; 
 int /*<<< orphan*/  il_setup_scan_deferred_work (struct il_priv*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static void
il3945_setup_deferred_work(struct il_priv *il)
{
	il->workqueue = create_singlethread_workqueue(DRV_NAME);

	init_waitqueue_head(&il->wait_command_queue);

	INIT_WORK(&il->restart, il3945_bg_restart);
	INIT_WORK(&il->rx_replenish, il3945_bg_rx_replenish);
	INIT_DELAYED_WORK(&il->init_alive_start, il3945_bg_init_alive_start);
	INIT_DELAYED_WORK(&il->alive_start, il3945_bg_alive_start);
	INIT_DELAYED_WORK(&il->_3945.rfkill_poll, il3945_rfkill_poll);

	il_setup_scan_deferred_work(il);

	il3945_hw_setup_deferred_work(il);

	init_timer(&il->watchdog);
	il->watchdog.data = (unsigned long)il;
	il->watchdog.function = il_bg_watchdog;

	tasklet_init(&il->irq_tasklet,
		     (void (*)(unsigned long))il3945_irq_tasklet,
		     (unsigned long)il);
}