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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  LINUX_MIB_TCPCHALLENGEACK ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 unsigned int sysctl_tcp_challenge_ack_limit ; 
 int /*<<< orphan*/  tcp_send_ack (struct sock*) ; 

__attribute__((used)) static void tcp_send_challenge_ack(struct sock *sk)
{
	/* unprotected vars, we dont care of overwrites */
	static u32 challenge_timestamp;
	static unsigned int challenge_count;
	u32 now = jiffies / HZ;

	if (now != challenge_timestamp) {
		challenge_timestamp = now;
		challenge_count = 0;
	}
	if (++challenge_count <= sysctl_tcp_challenge_ack_limit) {
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPCHALLENGEACK);
		tcp_send_ack(sk);
	}
}