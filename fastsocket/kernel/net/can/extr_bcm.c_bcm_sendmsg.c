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
typedef  int /*<<< orphan*/  u8 ;
struct socket {struct sock* sk; } ;
struct sockaddr_can {scalar_t__ can_family; int can_ifindex; } ;
struct sock {int dummy; } ;
struct net_device {scalar_t__ type; } ;
struct msghdr {int /*<<< orphan*/  msg_iov; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct bcm_sock {int ifindex; int /*<<< orphan*/  rx_ops; int /*<<< orphan*/  tx_ops; int /*<<< orphan*/  bound; } ;
struct bcm_msg_head {int opcode; int nframes; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 scalar_t__ AF_CAN ; 
 scalar_t__ ARPHRD_CAN ; 
 size_t CFSIZ ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOTCONN ; 
 size_t MHSIZ ; 
#define  RX_DELETE 134 
#define  RX_READ 133 
#define  RX_SETUP 132 
 int RX_STATUS ; 
#define  TX_DELETE 131 
#define  TX_READ 130 
#define  TX_SEND 129 
#define  TX_SETUP 128 
 int TX_STATUS ; 
 int /*<<< orphan*/  bcm_delete_rx_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_delete_tx_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bcm_read_op (int /*<<< orphan*/ *,struct bcm_msg_head*,int) ; 
 int bcm_rx_setup (struct bcm_msg_head*,struct msghdr*,int,struct sock*) ; 
 struct bcm_sock* bcm_sk (struct sock*) ; 
 int bcm_tx_send (struct msghdr*,int,struct sock*) ; 
 int bcm_tx_setup (struct bcm_msg_head*,struct msghdr*,int,struct sock*) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcpy_fromiovec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int bcm_sendmsg(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;
	struct bcm_sock *bo = bcm_sk(sk);
	int ifindex = bo->ifindex; /* default ifindex for this bcm_op */
	struct bcm_msg_head msg_head;
	int ret; /* read bytes or error codes as return value */

	if (!bo->bound)
		return -ENOTCONN;

	/* check for valid message length from userspace */
	if (size < MHSIZ || (size - MHSIZ) % CFSIZ)
		return -EINVAL;

	/* check for alternative ifindex for this bcm_op */

	if (!ifindex && msg->msg_name) {
		/* no bound device as default => check msg_name */
		struct sockaddr_can *addr =
			(struct sockaddr_can *)msg->msg_name;

		if (addr->can_family != AF_CAN)
			return -EINVAL;

		/* ifindex from sendto() */
		ifindex = addr->can_ifindex;

		if (ifindex) {
			struct net_device *dev;

			dev = dev_get_by_index(&init_net, ifindex);
			if (!dev)
				return -ENODEV;

			if (dev->type != ARPHRD_CAN) {
				dev_put(dev);
				return -ENODEV;
			}

			dev_put(dev);
		}
	}

	/* read message head information */

	ret = memcpy_fromiovec((u8 *)&msg_head, msg->msg_iov, MHSIZ);
	if (ret < 0)
		return ret;

	lock_sock(sk);

	switch (msg_head.opcode) {

	case TX_SETUP:
		ret = bcm_tx_setup(&msg_head, msg, ifindex, sk);
		break;

	case RX_SETUP:
		ret = bcm_rx_setup(&msg_head, msg, ifindex, sk);
		break;

	case TX_DELETE:
		if (bcm_delete_tx_op(&bo->tx_ops, msg_head.can_id, ifindex))
			ret = MHSIZ;
		else
			ret = -EINVAL;
		break;

	case RX_DELETE:
		if (bcm_delete_rx_op(&bo->rx_ops, msg_head.can_id, ifindex))
			ret = MHSIZ;
		else
			ret = -EINVAL;
		break;

	case TX_READ:
		/* reuse msg_head for the reply to TX_READ */
		msg_head.opcode  = TX_STATUS;
		ret = bcm_read_op(&bo->tx_ops, &msg_head, ifindex);
		break;

	case RX_READ:
		/* reuse msg_head for the reply to RX_READ */
		msg_head.opcode  = RX_STATUS;
		ret = bcm_read_op(&bo->rx_ops, &msg_head, ifindex);
		break;

	case TX_SEND:
		/* we need exactly one can_frame behind the msg head */
		if ((msg_head.nframes != 1) || (size != CFSIZ + MHSIZ))
			ret = -EINVAL;
		else
			ret = bcm_tx_send(msg, ifindex, sk);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	release_sock(sk);

	return ret;
}