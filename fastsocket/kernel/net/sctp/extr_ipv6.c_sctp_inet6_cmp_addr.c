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
struct TYPE_2__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct sock {int dummy; } ;
struct sctp_sock {int dummy; } ;
struct sctp_af {int (* cmp_addr ) (union sctp_addr const*,union sctp_addr const*) ;} ;

/* Variables and functions */
 scalar_t__ __ipv6_only_sock (struct sock*) ; 
 struct sctp_af* sctp_get_af_specific (scalar_t__) ; 
 scalar_t__ sctp_is_any (struct sock*,union sctp_addr const*) ; 
 struct sock* sctp_opt2sk (struct sctp_sock*) ; 
 int stub1 (union sctp_addr const*,union sctp_addr const*) ; 

__attribute__((used)) static int sctp_inet6_cmp_addr(const union sctp_addr *addr1,
			       const union sctp_addr *addr2,
			       struct sctp_sock *opt)
{
	struct sctp_af *af1, *af2;
	struct sock *sk = sctp_opt2sk(opt);

	af1 = sctp_get_af_specific(addr1->sa.sa_family);
	af2 = sctp_get_af_specific(addr2->sa.sa_family);

	if (!af1 || !af2)
		return 0;

	/* If the socket is IPv6 only, v4 addrs will not match */
	if (__ipv6_only_sock(sk) && af1 != af2)
		return 0;

	/* Today, wildcard AF_INET/AF_INET6. */
	if (sctp_is_any(sk, addr1) || sctp_is_any(sk, addr2))
		return 1;

	if (addr1->sa.sa_family != addr2->sa.sa_family)
		return 0;

	return af1->cmp_addr(addr1, addr2);
}