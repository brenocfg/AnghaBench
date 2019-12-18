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
struct sock {int sk_family; } ;
struct netlbl_lsm_secattr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ENOMSG ; 
 int EPROTONOSUPPORT ; 
 int cipso_v4_sock_getattr (struct sock*,struct netlbl_lsm_secattr*) ; 

int netlbl_sock_getattr(struct sock *sk,
			struct netlbl_lsm_secattr *secattr)
{
	int ret_val;

	switch (sk->sk_family) {
	case AF_INET:
		ret_val = cipso_v4_sock_getattr(sk, secattr);
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		ret_val = -ENOMSG;
		break;
#endif /* IPv6 */
	default:
		ret_val = -EPROTONOSUPPORT;
	}

	return ret_val;
}