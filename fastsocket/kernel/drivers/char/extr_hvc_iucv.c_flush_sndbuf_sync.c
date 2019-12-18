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
struct hvc_iucv_private {int /*<<< orphan*/  sndbuf_waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  tty_outqueue; int /*<<< orphan*/  sndbuf_work; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvc_iucv_send (struct hvc_iucv_private*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_outqueue_empty (struct hvc_iucv_private*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush_sndbuf_sync(struct hvc_iucv_private *priv)
{
	int sync_wait;

	cancel_delayed_work_sync(&priv->sndbuf_work);

	spin_lock_bh(&priv->lock);
	hvc_iucv_send(priv);		/* force sending buffered data */
	sync_wait = !list_empty(&priv->tty_outqueue); /* anything queued ? */
	spin_unlock_bh(&priv->lock);

	if (sync_wait)
		wait_event_timeout(priv->sndbuf_waitq,
				   tty_outqueue_empty(priv), HZ/10);
}