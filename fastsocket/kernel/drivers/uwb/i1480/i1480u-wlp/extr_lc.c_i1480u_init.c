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
struct i1480u {int /*<<< orphan*/  wlp; int /*<<< orphan*/  rssi_stats; int /*<<< orphan*/  lqe_stats; int /*<<< orphan*/  notif_edc; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  options; int /*<<< orphan*/  tx_list_lock; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_options_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void i1480u_init(struct i1480u *i1480u)
{
	/* nothing so far... doesn't it suck? */
	spin_lock_init(&i1480u->lock);
	INIT_LIST_HEAD(&i1480u->tx_list);
	spin_lock_init(&i1480u->tx_list_lock);
	wlp_options_init(&i1480u->options);
	edc_init(&i1480u->tx_errors);
	edc_init(&i1480u->rx_errors);
#ifdef i1480u_FLOW_CONTROL
	edc_init(&i1480u->notif_edc);
#endif
	stats_init(&i1480u->lqe_stats);
	stats_init(&i1480u->rssi_stats);
	wlp_init(&i1480u->wlp);
}