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
struct hvc_struct {int dummy; } ;
struct hvc_iucv_private {int /*<<< orphan*/  lock; scalar_t__ sndbuf_len; int /*<<< orphan*/  tty_state; int /*<<< orphan*/  tty_inqueue; int /*<<< orphan*/  tty_outqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_CLOSED ; 
 int /*<<< orphan*/  destroy_tty_buffer_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_sndbuf_sync (struct hvc_iucv_private*) ; 
 struct hvc_iucv_private* hvc_iucv_get_private (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvc_iucv_notifier_del(struct hvc_struct *hp, int id)
{
	struct hvc_iucv_private *priv;

	priv = hvc_iucv_get_private(id);
	if (!priv)
		return;

	flush_sndbuf_sync(priv);

	spin_lock_bh(&priv->lock);
	destroy_tty_buffer_list(&priv->tty_outqueue);
	destroy_tty_buffer_list(&priv->tty_inqueue);
	priv->tty_state = TTY_CLOSED;
	priv->sndbuf_len = 0;
	spin_unlock_bh(&priv->lock);
}