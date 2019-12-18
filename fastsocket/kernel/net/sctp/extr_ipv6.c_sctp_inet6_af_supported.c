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
struct sctp_sock {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  __ipv6_only_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 

__attribute__((used)) static int sctp_inet6_af_supported(sa_family_t family, struct sctp_sock *sp)
{
	switch (family) {
	case AF_INET6:
		return 1;
	/* v4-mapped-v6 addresses */
	case AF_INET:
		if (!__ipv6_only_sock(sctp_opt2sk(sp)))
			return 1;
	default:
		return 0;
	}
}