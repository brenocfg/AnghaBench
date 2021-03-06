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
struct sockaddr_can {int /*<<< orphan*/  can_ifindex; int /*<<< orphan*/  can_family; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ cb; int /*<<< orphan*/  tstamp; } ;
struct can_frame {unsigned int nframes; int /*<<< orphan*/  can_dlc; } ;
struct bcm_sock {int /*<<< orphan*/  dropped_usr_msgs; } ;
struct bcm_op {int /*<<< orphan*/  rx_ifindex; int /*<<< orphan*/  rx_stamp; struct sock* sk; } ;
struct bcm_msg_head {unsigned int nframes; int /*<<< orphan*/  can_dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CAN ; 
 int /*<<< orphan*/  BCM_CAN_DLC_MASK ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int CFSIZ ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct bcm_sock* bcm_sk (struct sock*) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct can_frame*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_can*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void bcm_send_to_user(struct bcm_op *op, struct bcm_msg_head *head,
			     struct can_frame *frames, int has_timestamp)
{
	struct sk_buff *skb;
	struct can_frame *firstframe;
	struct sockaddr_can *addr;
	struct sock *sk = op->sk;
	unsigned int datalen = head->nframes * CFSIZ;
	int err;

	skb = alloc_skb(sizeof(*head) + datalen, gfp_any());
	if (!skb)
		return;

	memcpy(skb_put(skb, sizeof(*head)), head, sizeof(*head));

	if (head->nframes) {
		/* can_frames starting here */
		firstframe = (struct can_frame *)skb_tail_pointer(skb);

		memcpy(skb_put(skb, datalen), frames, datalen);

		/*
		 * the BCM uses the can_dlc-element of the can_frame
		 * structure for internal purposes. This is only
		 * relevant for updates that are generated by the
		 * BCM, where nframes is 1
		 */
		if (head->nframes == 1)
			firstframe->can_dlc &= BCM_CAN_DLC_MASK;
	}

	if (has_timestamp) {
		/* restore rx timestamp */
		skb->tstamp = op->rx_stamp;
	}

	/*
	 *  Put the datagram to the queue so that bcm_recvmsg() can
	 *  get it from there.  We need to pass the interface index to
	 *  bcm_recvmsg().  We pass a whole struct sockaddr_can in skb->cb
	 *  containing the interface index.
	 */

	BUILD_BUG_ON(sizeof(skb->cb) < sizeof(struct sockaddr_can));
	addr = (struct sockaddr_can *)skb->cb;
	memset(addr, 0, sizeof(*addr));
	addr->can_family  = AF_CAN;
	addr->can_ifindex = op->rx_ifindex;

	err = sock_queue_rcv_skb(sk, skb);
	if (err < 0) {
		struct bcm_sock *bo = bcm_sk(sk);

		kfree_skb(skb);
		/* don't care about overflows in this statistic */
		bo->dropped_usr_msgs++;
	}
}