#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; void* dev; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iov; } ;
struct kiocb {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  raw_q; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {unsigned char pkt_type; } ;
struct TYPE_5__ {struct hci_dev* hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ocf_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EBADFD ; 
 int EFAULT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 unsigned char HCI_COMMAND_PKT ; 
 size_t HCI_FLT_OCF_BITS ; 
 size_t HCI_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  HCI_RAW ; 
 size_t HCI_SFLT_MAX_OGF ; 
 int MSG_DONTWAIT ; 
 int MSG_ERRQUEUE ; 
 int MSG_NOSIGNAL ; 
 int MSG_OOB ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_send_alloc (struct sock*,size_t,int,int*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 size_t get_unaligned_le16 (scalar_t__) ; 
 size_t hci_opcode_ocf (size_t) ; 
 size_t hci_opcode_ogf (size_t) ; 
 TYPE_2__* hci_pi (struct sock*) ; 
 int /*<<< orphan*/  hci_sched_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sched_tx (struct hci_dev*) ; 
 TYPE_1__ hci_sec_filter ; 
 int /*<<< orphan*/  hci_test_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ memcpy_fromiovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_sock_sendmsg(struct kiocb *iocb, struct socket *sock,
			    struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
	struct hci_dev *hdev;
	struct sk_buff *skb;
	int err;

	BT_DBG("sock %p sk %p", sock, sk);

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (msg->msg_flags & ~(MSG_DONTWAIT|MSG_NOSIGNAL|MSG_ERRQUEUE))
		return -EINVAL;

	if (len < 4 || len > HCI_MAX_FRAME_SIZE)
		return -EINVAL;

	lock_sock(sk);

	if (!(hdev = hci_pi(sk)->hdev)) {
		err = -EBADFD;
		goto done;
	}

	if (!(skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err)))
		goto done;

	if (memcpy_fromiovec(skb_put(skb, len), msg->msg_iov, len)) {
		err = -EFAULT;
		goto drop;
	}

	bt_cb(skb)->pkt_type = *((unsigned char *) skb->data);
	skb_pull(skb, 1);
	skb->dev = (void *) hdev;

	if (bt_cb(skb)->pkt_type == HCI_COMMAND_PKT) {
		u16 opcode = get_unaligned_le16(skb->data);
		u16 ogf = hci_opcode_ogf(opcode);
		u16 ocf = hci_opcode_ocf(opcode);

		if (((ogf > HCI_SFLT_MAX_OGF) ||
				!hci_test_bit(ocf & HCI_FLT_OCF_BITS, &hci_sec_filter.ocf_mask[ogf])) &&
					!capable(CAP_NET_RAW)) {
			err = -EPERM;
			goto drop;
		}

		if (test_bit(HCI_RAW, &hdev->flags) || (ogf == 0x3f)) {
			skb_queue_tail(&hdev->raw_q, skb);
			hci_sched_tx(hdev);
		} else {
			skb_queue_tail(&hdev->cmd_q, skb);
			hci_sched_cmd(hdev);
		}
	} else {
		if (!capable(CAP_NET_RAW)) {
			err = -EPERM;
			goto drop;
		}

		skb_queue_tail(&hdev->raw_q, skb);
		hci_sched_tx(hdev);
	}

	err = len;

done:
	release_sock(sk);
	return err;

drop:
	kfree_skb(skb);
	goto done;
}