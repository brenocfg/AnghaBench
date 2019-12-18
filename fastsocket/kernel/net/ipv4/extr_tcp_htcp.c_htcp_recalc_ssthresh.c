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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {int snd_cwnd; } ;
struct sock {int dummy; } ;
struct htcp {int beta; } ;

/* Variables and functions */
 int /*<<< orphan*/  htcp_param_update (struct sock*) ; 
 struct htcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 htcp_recalc_ssthresh(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct htcp *ca = inet_csk_ca(sk);

	htcp_param_update(sk);
	return max((tp->snd_cwnd * ca->beta) >> 7, 2U);
}