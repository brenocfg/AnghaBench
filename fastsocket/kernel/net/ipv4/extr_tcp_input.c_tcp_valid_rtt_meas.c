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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_backoff; } ;

/* Variables and functions */
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_rtt_estimator (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_rto (struct sock*) ; 

void tcp_valid_rtt_meas(struct sock *sk, u32 seq_rtt)
{
	tcp_rtt_estimator(sk, seq_rtt);
	tcp_set_rto(sk);
	inet_csk(sk)->icsk_backoff = 0;
}