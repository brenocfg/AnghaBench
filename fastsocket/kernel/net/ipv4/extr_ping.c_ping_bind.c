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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_userlocks; scalar_t__ sk_bound_dev_if; } ;
struct inet_sock {scalar_t__ freebind; scalar_t__ transparent; scalar_t__ num; scalar_t__ rcv_saddr; scalar_t__ saddr; scalar_t__ dport; scalar_t__ daddr; int /*<<< orphan*/  sport; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int RTN_BROADCAST ; 
 int RTN_LOCAL ; 
 int RTN_MULTICAST ; 
 int /*<<< orphan*/  SOCK_BINDADDR_LOCK ; 
 int /*<<< orphan*/  SOCK_BINDPORT_LOCK ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int inet_addr_type (int /*<<< orphan*/ ,scalar_t__) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ ping_v4_get_port (struct sock*,unsigned short) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ sysctl_ip_nonlocal_bind ; 

__attribute__((used)) static int ping_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct sockaddr_in *addr = (struct sockaddr_in *)uaddr;
	struct inet_sock *isk = inet_sk(sk);
	unsigned short snum;
	int chk_addr_ret;
	int err;

	if (addr_len < sizeof(struct sockaddr_in))
		return -EINVAL;

	pr_debug("ping_v4_bind(sk=%p,sa_addr=%08x,sa_port=%d)\n",
		sk, addr->sin_addr.s_addr, ntohs(addr->sin_port));

	chk_addr_ret = inet_addr_type(sock_net(sk), addr->sin_addr.s_addr);
	if (addr->sin_addr.s_addr == htonl(INADDR_ANY))
		chk_addr_ret = RTN_LOCAL;

	if ((sysctl_ip_nonlocal_bind == 0 &&
	    isk->freebind == 0 && isk->transparent == 0 &&
	     chk_addr_ret != RTN_LOCAL) ||
	    chk_addr_ret == RTN_MULTICAST ||
	    chk_addr_ret == RTN_BROADCAST)
		return -EADDRNOTAVAIL;

	lock_sock(sk);

	err = -EINVAL;
	if (isk->num != 0)
		goto out;

	err = -EADDRINUSE;
	isk->rcv_saddr = isk->saddr = addr->sin_addr.s_addr;
	snum = ntohs(addr->sin_port);
	if (ping_v4_get_port(sk, snum) != 0) {
		isk->saddr = isk->rcv_saddr = 0;
		goto out;
	}

	pr_debug("after bind(): num = %d, daddr = %pI4, dif = %d\n",
		(int)isk->num,
		&isk->rcv_saddr,
		(int)sk->sk_bound_dev_if);

	err = 0;
	if (isk->rcv_saddr)
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
	if (snum)
		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
	isk->sport = htons(isk->num);
	isk->daddr = 0;
	isk->dport = 0;
	sk_dst_reset(sk);
out:
	release_sock(sk);
	pr_debug("ping_v4_bind -> %d\n", err);
	return err;
}