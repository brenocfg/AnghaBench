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
struct sock {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {scalar_t__ cipso; scalar_t__ __data; } ;
struct TYPE_2__ {int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 int ENOMSG ; 
 int cipso_v4_getattr (scalar_t__,struct netlbl_lsm_secattr*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 struct ip_options* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int cipso_v4_sock_getattr(struct sock *sk, struct netlbl_lsm_secattr *secattr)
{
	struct ip_options *opt;
	int res = -ENOMSG;

	rcu_read_lock();
	opt = rcu_dereference(inet_sk(sk)->opt);
	if (opt && opt->cipso)
		res = cipso_v4_getattr(opt->__data +
						opt->cipso -
						sizeof(struct iphdr),
				       secattr);
	rcu_read_unlock();
	return res;
}