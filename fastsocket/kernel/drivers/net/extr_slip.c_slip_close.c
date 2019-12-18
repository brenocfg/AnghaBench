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
struct tty_struct {struct slip* disc_data; } ;
struct slip {scalar_t__ magic; int /*<<< orphan*/  dev; int /*<<< orphan*/  outfill_timer; int /*<<< orphan*/  keepalive_timer; scalar_t__ line; int /*<<< orphan*/  leased; struct tty_struct* tty; } ;

/* Variables and functions */
 scalar_t__ SLIP_MAGIC ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slip_close(struct tty_struct *tty)
{
	struct slip *sl = tty->disc_data;

	/* First make sure we're connected. */
	if (!sl || sl->magic != SLIP_MAGIC || sl->tty != tty)
		return;

	tty->disc_data = NULL;
	sl->tty = NULL;
	if (!sl->leased)
		sl->line = 0;

	/* VSV = very important to remove timers */
#ifdef CONFIG_SLIP_SMART
	del_timer_sync(&sl->keepalive_timer);
	del_timer_sync(&sl->outfill_timer);
#endif
	/* Flush network side */
	unregister_netdev(sl->dev);
	/* This will complete via sl_free_netdev */
}