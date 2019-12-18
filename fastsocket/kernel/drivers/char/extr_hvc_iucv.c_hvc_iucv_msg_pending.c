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
struct iucv_message {scalar_t__ length; } ;
struct iucv_tty_buffer {int /*<<< orphan*/  list; struct iucv_message msg; } ;
struct iucv_path {struct hvc_iucv_private* private; } ;
struct hvc_iucv_private {scalar_t__ tty_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  tty_inqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MSG_MAX_DATALEN ; 
 scalar_t__ MSG_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ TTY_CLOSED ; 
 struct iucv_tty_buffer* alloc_tty_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvc_kick () ; 
 int /*<<< orphan*/  iucv_message_reject (struct iucv_path*,struct iucv_message*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvc_iucv_msg_pending(struct iucv_path *path,
				 struct iucv_message *msg)
{
	struct hvc_iucv_private *priv = path->private;
	struct iucv_tty_buffer *rb;

	/* reject messages that exceed max size of iucv_tty_msg->datalen */
	if (msg->length > MSG_SIZE(MSG_MAX_DATALEN)) {
		iucv_message_reject(path, msg);
		return;
	}

	spin_lock(&priv->lock);

	/* reject messages if tty has not yet been opened */
	if (priv->tty_state == TTY_CLOSED) {
		iucv_message_reject(path, msg);
		goto unlock_return;
	}

	/* allocate tty buffer to save iucv msg only */
	rb = alloc_tty_buffer(0, GFP_ATOMIC);
	if (!rb) {
		iucv_message_reject(path, msg);
		goto unlock_return;	/* -ENOMEM */
	}
	rb->msg = *msg;

	list_add_tail(&rb->list, &priv->tty_inqueue);

	hvc_kick();	/* wake up hvc thread */

unlock_return:
	spin_unlock(&priv->lock);
}