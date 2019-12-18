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
struct iucv_message {int dummy; } ;
struct sock_msg_q {int /*<<< orphan*/  list; struct iucv_message msg; struct iucv_path* path; } ;
struct sock {int sk_shutdown; int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct iucv_sock {TYPE_1__ message_q; int /*<<< orphan*/  backlog_skb_q; } ;
struct iucv_path {struct sock* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* message_reject ) (struct iucv_path*,struct iucv_message*) ;} ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int RCV_SHUTDOWN ; 
 struct sk_buff* alloc_skb (scalar_t__,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ iucv_msg_length (struct iucv_message*) ; 
 int /*<<< orphan*/  iucv_process_message (struct sock*,struct sk_buff*,struct iucv_path*,struct iucv_message*) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 struct sock_msg_q* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* pr_iucv ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,struct iucv_message*) ; 

__attribute__((used)) static void iucv_callback_rx(struct iucv_path *path, struct iucv_message *msg)
{
	struct sock *sk = path->private;
	struct iucv_sock *iucv = iucv_sk(sk);
	struct sk_buff *skb;
	struct sock_msg_q *save_msg;
	int len;

	if (sk->sk_shutdown & RCV_SHUTDOWN) {
		pr_iucv->message_reject(path, msg);
		return;
	}

	spin_lock(&iucv->message_q.lock);

	if (!list_empty(&iucv->message_q.list) ||
	    !skb_queue_empty(&iucv->backlog_skb_q))
		goto save_message;

	len = atomic_read(&sk->sk_rmem_alloc);
	len += iucv_msg_length(msg) + sizeof(struct sk_buff);
	if (len > sk->sk_rcvbuf)
		goto save_message;

	skb = alloc_skb(iucv_msg_length(msg), GFP_ATOMIC | GFP_DMA);
	if (!skb)
		goto save_message;

	iucv_process_message(sk, skb, path, msg);
	goto out_unlock;

save_message:
	save_msg = kzalloc(sizeof(struct sock_msg_q), GFP_ATOMIC | GFP_DMA);
	if (!save_msg)
		goto out_unlock;
	save_msg->path = path;
	save_msg->msg = *msg;

	list_add_tail(&save_msg->list, &iucv->message_q.list);

out_unlock:
	spin_unlock(&iucv->message_q.lock);
}