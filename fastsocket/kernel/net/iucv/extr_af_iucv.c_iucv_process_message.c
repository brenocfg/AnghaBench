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
struct sock {scalar_t__ sk_type; int sk_rcvbuf; } ;
struct sk_buff {unsigned int len; int truesize; int /*<<< orphan*/ * data; } ;
struct iucv_path {int dummy; } ;
struct iucv_message {int flags; int /*<<< orphan*/  rmmsg; int /*<<< orphan*/  class; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog_skb_q; } ;
struct TYPE_3__ {int (* message_receive ) (struct iucv_path*,struct iucv_message*,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* path_sever ) (struct iucv_path*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CB_TRGCLS (struct sk_buff*) ; 
 int /*<<< orphan*/  CB_TRGCLS_LEN ; 
 int IUCV_IPRMDATA ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  iprm_shutdown ; 
 int iucv_fragment_skb (struct sock*,struct sk_buff*,unsigned int) ; 
 unsigned int iucv_msg_length (struct iucv_message*) ; 
 TYPE_2__* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* pr_iucv ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int stub1 (struct iucv_path*,struct iucv_message*,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct iucv_path*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iucv_process_message(struct sock *sk, struct sk_buff *skb,
				 struct iucv_path *path,
				 struct iucv_message *msg)
{
	int rc;
	unsigned int len;

	len = iucv_msg_length(msg);

	/* store msg target class in the second 4 bytes of skb ctrl buffer */
	/* Note: the first 4 bytes are reserved for msg tag */
	memcpy(CB_TRGCLS(skb), &msg->class, CB_TRGCLS_LEN);

	/* check for special IPRM messages (e.g. iucv_sock_shutdown) */
	if ((msg->flags & IUCV_IPRMDATA) && len > 7) {
		if (memcmp(msg->rmmsg, iprm_shutdown, 8) == 0) {
			skb->data = NULL;
			skb->len = 0;
		}
	} else {
		rc = pr_iucv->message_receive(path, msg,
					      msg->flags & IUCV_IPRMDATA,
					      skb->data, len, NULL);
		if (rc) {
			kfree_skb(skb);
			return;
		}
		/* we need to fragment iucv messages for SOCK_STREAM only;
		 * for SOCK_SEQPACKET, it is only relevant if we support
		 * record segmentation using MSG_EOR (see also recvmsg()) */
		if (sk->sk_type == SOCK_STREAM &&
		    skb->truesize >= sk->sk_rcvbuf / 4) {
			rc = iucv_fragment_skb(sk, skb, len);
			kfree_skb(skb);
			skb = NULL;
			if (rc) {
				pr_iucv->path_sever(path, NULL);
				return;
			}
			skb = skb_dequeue(&iucv_sk(sk)->backlog_skb_q);
		} else {
			skb_reset_transport_header(skb);
			skb_reset_network_header(skb);
			skb->len = len;
		}
	}

	if (sock_queue_rcv_skb(sk, skb))
		skb_queue_head(&iucv_sk(sk)->backlog_skb_q, skb);
}