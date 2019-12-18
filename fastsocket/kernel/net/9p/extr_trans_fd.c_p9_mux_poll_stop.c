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
struct p9_poll_wait {int /*<<< orphan*/ * wait_addr; int /*<<< orphan*/  wait; } ;
struct p9_conn {int /*<<< orphan*/  poll_pending_link; struct p9_poll_wait* poll_wait; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct p9_poll_wait*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_poll_lock ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void p9_mux_poll_stop(struct p9_conn *m)
{
	unsigned long flags;
	int i;

	for (i = 0; i < ARRAY_SIZE(m->poll_wait); i++) {
		struct p9_poll_wait *pwait = &m->poll_wait[i];

		if (pwait->wait_addr) {
			remove_wait_queue(pwait->wait_addr, &pwait->wait);
			pwait->wait_addr = NULL;
		}
	}

	spin_lock_irqsave(&p9_poll_lock, flags);
	list_del_init(&m->poll_pending_link);
	spin_unlock_irqrestore(&p9_poll_lock, flags);
}