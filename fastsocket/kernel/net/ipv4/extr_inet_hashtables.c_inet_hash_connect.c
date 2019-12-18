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
struct sock {int dummy; } ;
struct inet_timewait_death_row {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inet_check_established ; 
 int __inet_hash_connect (struct inet_timewait_death_row*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inet_hash_nolisten ; 
 scalar_t__ enable_receive_flow_deliver ; 
 int /*<<< orphan*/  inet_sk_port_offset (struct sock*) ; 
 int rfd_inet_hash_connect (struct inet_timewait_death_row*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int inet_hash_connect(struct inet_timewait_death_row *death_row,
		      struct sock *sk)
{
	int ret;
	if (enable_receive_flow_deliver)
		ret = rfd_inet_hash_connect(death_row, sk, inet_sk_port_offset(sk),
				__inet_check_established, __inet_hash_nolisten);
	else
		ret = __inet_hash_connect(death_row, sk, inet_sk_port_offset(sk),
			__inet_check_established, __inet_hash_nolisten);

	return ret;
}