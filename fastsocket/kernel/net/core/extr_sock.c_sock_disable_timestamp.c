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

/* Variables and functions */
 int SOCK_TIMESTAMP ; 
 int SOCK_TIMESTAMPING_RX_SOFTWARE ; 
 int /*<<< orphan*/  net_disable_timestamp () ; 
 scalar_t__ sock_flag (struct sock*,int) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int) ; 

__attribute__((used)) static void sock_disable_timestamp(struct sock *sk, int flag)
{
	if (sock_flag(sk, flag)) {
		sock_reset_flag(sk, flag);
		if (!sock_flag(sk, SOCK_TIMESTAMP) &&
		    !sock_flag(sk, SOCK_TIMESTAMPING_RX_SOFTWARE)) {
			net_disable_timestamp();
		}
	}
}