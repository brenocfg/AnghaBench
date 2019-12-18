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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_3__ {int /*<<< orphan*/  s6_addr32; } ;
struct ipv6_pinfo {TYPE_2__ daddr; TYPE_1__ rcv_saddr; } ;
struct inet_sock {int /*<<< orphan*/  dport; } ;

/* Variables and functions */
 struct ipv6_pinfo* inet6_sk (struct sock const*) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  secure_ipv6_port_ephemeral (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 inet6_sk_port_offset(const struct sock *sk)
{
	const struct inet_sock *inet = inet_sk(sk);
	const struct ipv6_pinfo *np = inet6_sk(sk);
	return secure_ipv6_port_ephemeral(np->rcv_saddr.s6_addr32,
					  np->daddr.s6_addr32,
					  inet->dport);
}