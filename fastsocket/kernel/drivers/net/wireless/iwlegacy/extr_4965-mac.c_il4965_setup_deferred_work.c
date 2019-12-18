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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct il_priv {int /*<<< orphan*/  irq_tasklet; TYPE_1__ watchdog; TYPE_1__ stats_periodic; int /*<<< orphan*/  txpower_work; int /*<<< orphan*/  alive_start; int /*<<< orphan*/  init_alive_start; int /*<<< orphan*/  run_time_calib_work; int /*<<< orphan*/  rx_replenish; int /*<<< orphan*/  restart; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_bg_alive_start ; 
 int /*<<< orphan*/  il4965_bg_init_alive_start ; 
 int /*<<< orphan*/  il4965_bg_restart ; 
 int /*<<< orphan*/  il4965_bg_run_time_calib_work ; 
 int /*<<< orphan*/  il4965_bg_rx_replenish ; 
 int /*<<< orphan*/  il4965_bg_stats_periodic ; 
 int /*<<< orphan*/  il4965_bg_txpower_work ; 
 scalar_t__ il4965_irq_tasklet ; 
 int /*<<< orphan*/  il_bg_watchdog ; 
 int /*<<< orphan*/  il_setup_scan_deferred_work (struct il_priv*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static void
il4965_setup_deferred_work(struct il_priv *il)
{
	il->workqueue = create_singlethread_workqueue(DRV_NAME);

	init_waitqueue_head(&il->wait_command_queue);

	INIT_WORK(&il->restart, il4965_bg_restart);
	INIT_WORK(&il->rx_replenish, il4965_bg_rx_replenish);
	INIT_WORK(&il->run_time_calib_work, il4965_bg_run_time_calib_work);
	INIT_DELAYED_WORK(&il->init_alive_start, il4965_bg_init_alive_start);
	INIT_DELAYED_WORK(&il->alive_start, il4965_bg_alive_start);

	il_setup_scan_deferred_work(il);

	INIT_WORK(&il->txpower_work, il4965_bg_txpower_work);

	init_timer(&il->stats_periodic);
	il->stats_periodic.data = (unsigned long)il;
	il->stats_periodic.function = il4965_bg_stats_periodic;

	init_timer(&il->watchdog);
	il->watchdog.data = (unsigned long)il;
	il->watchdog.function = il_bg_watchdog;

	tasklet_init(&il->irq_tasklet,
		     (void (*)(unsigned long))il4965_irq_tasklet,
		     (unsigned long)il);
}