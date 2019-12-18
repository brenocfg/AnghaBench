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
struct dccp_sock {int /*<<< orphan*/  dccps_xmit_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_write_xmit (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void dccp_write_xmit_timer(unsigned long data)
{
	struct sock *sk = (struct sock *)data;
	struct dccp_sock *dp = dccp_sk(sk);

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk))
		sk_reset_timer(sk, &dp->dccps_xmit_timer, jiffies+1);
	else
		dccp_write_xmit(sk, 0);
	bh_unlock_sock(sk);
	sock_put(sk);
}