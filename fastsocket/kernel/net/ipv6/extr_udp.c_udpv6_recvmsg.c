#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; scalar_t__ protocol; } ;
struct msghdr {int msg_flags; scalar_t__ msg_name; int /*<<< orphan*/  msg_iov; } ;
struct kiocb {int dummy; } ;
struct TYPE_7__ {scalar_t__ all; } ;
struct ipv6_pinfo {TYPE_1__ rxopt; } ;
struct inet_sock {scalar_t__ cmsg_flags; } ;
struct TYPE_12__ {scalar_t__ iif; } ;
struct TYPE_11__ {scalar_t__ partial_cov; } ;
struct TYPE_10__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 TYPE_6__* IP6CB (struct sk_buff*) ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IS_UDPLITE (struct sock*) ; 
 int MSG_DONTWAIT ; 
 int MSG_ERRQUEUE ; 
 int MSG_TRUNC ; 
 int /*<<< orphan*/  UDP6_INC_STATS_USER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_INC_STATS_USER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_MIB_INDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 TYPE_5__* UDP_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_recv_datagram (struct sock*,int,int*,int*) ; 
 int /*<<< orphan*/  datagram_recv_ctl (struct sock*,struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_cmsg_recv (struct msghdr*,struct sk_buff*) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_recv_error (struct sock*,struct msghdr*,size_t,int*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_copy_and_csum_datagram_iovec (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_free_datagram_locked (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_kill_datagram (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_recv_ts_and_drops (struct msghdr*,struct sock*,struct sk_buff*) ; 
 TYPE_2__* udp_hdr (struct sk_buff*) ; 
 scalar_t__ udp_lib_checksum_complete (struct sk_buff*) ; 

int udpv6_recvmsg(struct kiocb *iocb, struct sock *sk,
		  struct msghdr *msg, size_t len,
		  int noblock, int flags, int *addr_len)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct sk_buff *skb;
	unsigned int ulen, copied;
	int peeked;
	int err;
	int is_udplite = IS_UDPLITE(sk);
	int is_udp4;

	if (flags & MSG_ERRQUEUE)
		return ipv6_recv_error(sk, msg, len, addr_len);

try_again:
	skb = __skb_recv_datagram(sk, flags | (noblock ? MSG_DONTWAIT : 0),
				  &peeked, &err);
	if (!skb)
		goto out;

	ulen = skb->len - sizeof(struct udphdr);
	copied = len;
	if (copied > ulen)
		copied = ulen;
	else if (copied < ulen)
		msg->msg_flags |= MSG_TRUNC;

	is_udp4 = (skb->protocol == htons(ETH_P_IP));

	/*
	 * If checksum is needed at all, try to do it while copying the
	 * data.  If the data is truncated, or if we only want a partial
	 * coverage checksum (UDP-Lite), do it before the copy.
	 */

	if (copied < ulen || UDP_SKB_CB(skb)->partial_cov) {
		if (udp_lib_checksum_complete(skb))
			goto csum_copy_err;
	}

	if (skb_csum_unnecessary(skb))
		err = skb_copy_datagram_iovec(skb, sizeof(struct udphdr),
					      msg->msg_iov, copied       );
	else {
		err = skb_copy_and_csum_datagram_iovec(skb, sizeof(struct udphdr), msg->msg_iov);
		if (err == -EINVAL)
			goto csum_copy_err;
	}
	if (err)
		goto out_free;

	if (!peeked) {
		if (is_udp4)
			UDP_INC_STATS_USER(sock_net(sk),
					UDP_MIB_INDATAGRAMS, is_udplite);
		else
			UDP6_INC_STATS_USER(sock_net(sk),
					UDP_MIB_INDATAGRAMS, is_udplite);
	}

	sock_recv_ts_and_drops(msg, sk, skb);

	/* Copy the address. */
	if (msg->msg_name) {
		struct sockaddr_in6 *sin6;

		sin6 = (struct sockaddr_in6 *) msg->msg_name;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = udp_hdr(skb)->source;
		sin6->sin6_flowinfo = 0;
		sin6->sin6_scope_id = 0;

		if (is_udp4)
			ipv6_addr_set(&sin6->sin6_addr, 0, 0,
				      htonl(0xffff), ip_hdr(skb)->saddr);
		else {
			ipv6_addr_copy(&sin6->sin6_addr,
				       &ipv6_hdr(skb)->saddr);
			if (ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL)
				sin6->sin6_scope_id = IP6CB(skb)->iif;
		}
		*addr_len = sizeof(*sin6);
	}
	if (is_udp4) {
		if (inet->cmsg_flags)
			ip_cmsg_recv(msg, skb);
	} else {
		if (np->rxopt.all)
			datagram_recv_ctl(sk, msg, skb);
	}

	err = copied;
	if (flags & MSG_TRUNC)
		err = ulen;

out_free:
	skb_free_datagram_locked(sk, skb);
out:
	return err;

csum_copy_err:
	lock_sock(sk);
	if (!skb_kill_datagram(sk, skb, flags)) {
		if (is_udp4)
			UDP_INC_STATS_USER(sock_net(sk),
					UDP_MIB_INERRORS, is_udplite);
		else
			UDP6_INC_STATS_USER(sock_net(sk),
					UDP_MIB_INERRORS, is_udplite);
	}
	release_sock(sk);

	if (flags & MSG_DONTWAIT)
		return -EAGAIN;
	goto try_again;
}