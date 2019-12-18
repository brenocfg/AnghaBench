#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ pg_vec; } ;
struct packet_sock {TYPE_1__ tx_ring; } ;
struct msghdr {int dummy; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 int packet_snd (struct socket*,struct msghdr*,size_t) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int tpacket_snd (struct packet_sock*,struct msghdr*) ; 

__attribute__((used)) static int packet_sendmsg(struct kiocb *iocb, struct socket *sock,
		struct msghdr *msg, size_t len)
{
#ifdef CONFIG_PACKET_MMAP
	struct sock *sk = sock->sk;
	struct packet_sock *po = pkt_sk(sk);
	if (po->tx_ring.pg_vec)
		return tpacket_snd(po, msg);
	else
#endif
		return packet_snd(sock, msg, len);
}