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
struct tty_struct {struct mkiss* disc_data; } ;
struct mkiss {int /*<<< orphan*/ * tty; int /*<<< orphan*/  xbuff; int /*<<< orphan*/  rbuff; int /*<<< orphan*/  dev; int /*<<< orphan*/  dead_sem; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mkiss_close(struct tty_struct *tty)
{
	struct mkiss *ax;

	write_lock(&disc_data_lock);
	ax = tty->disc_data;
	tty->disc_data = NULL;
	write_unlock(&disc_data_lock);

	if (!ax)
		return;

	/*
	 * We have now ensured that nobody can start using ap from now on, but
	 * we have to wait for all existing users to finish.
	 */
	if (!atomic_dec_and_test(&ax->refcnt))
		down(&ax->dead_sem);

	unregister_netdev(ax->dev);

	/* Free all AX25 frame buffers. */
	kfree(ax->rbuff);
	kfree(ax->xbuff);

	ax->tty = NULL;
}