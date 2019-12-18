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
struct tty_struct {int dummy; } ;
struct moxa_board_conf {unsigned int numPorts; TYPE_2__* ports; int /*<<< orphan*/ * basemem; scalar_t__ ready; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  moxa_lock ; 
 int /*<<< orphan*/  moxa_openlock ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_1__*) ; 

__attribute__((used)) static void moxa_board_deinit(struct moxa_board_conf *brd)
{
	unsigned int a, opened;

	mutex_lock(&moxa_openlock);
	spin_lock_bh(&moxa_lock);
	brd->ready = 0;
	spin_unlock_bh(&moxa_lock);

	/* pci hot-un-plug support */
	for (a = 0; a < brd->numPorts; a++)
		if (brd->ports[a].port.flags & ASYNC_INITIALIZED) {
			struct tty_struct *tty = tty_port_tty_get(
						&brd->ports[a].port);
			if (tty) {
				tty_hangup(tty);
				tty_kref_put(tty);
			}
		}
	while (1) {
		opened = 0;
		for (a = 0; a < brd->numPorts; a++)
			if (brd->ports[a].port.flags & ASYNC_INITIALIZED)
				opened++;
		mutex_unlock(&moxa_openlock);
		if (!opened)
			break;
		msleep(50);
		mutex_lock(&moxa_openlock);
	}

	iounmap(brd->basemem);
	brd->basemem = NULL;
	kfree(brd->ports);
}