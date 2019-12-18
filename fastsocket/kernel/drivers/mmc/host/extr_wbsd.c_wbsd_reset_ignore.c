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
struct wbsd_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  card_tasklet; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  WBSD_FIGNORE_DETECT ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wbsd_reset_ignore(unsigned long data)
{
	struct wbsd_host *host = (struct wbsd_host *)data;

	BUG_ON(host == NULL);

	DBG("Resetting card detection ignore\n");

	spin_lock_bh(&host->lock);

	host->flags &= ~WBSD_FIGNORE_DETECT;

	/*
	 * Card status might have changed during the
	 * blackout.
	 */
	tasklet_schedule(&host->card_tasklet);

	spin_unlock_bh(&host->lock);
}