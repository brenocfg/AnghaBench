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
struct sock {int dummy; } ;
struct illinois {scalar_t__ base_rtt; scalar_t__ max_rtt; int /*<<< orphan*/  sum_rtt; int /*<<< orphan*/  cnt_rtt; int /*<<< orphan*/  acked; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ RTT_MAX ; 
 struct illinois* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void tcp_illinois_acked(struct sock *sk, u32 pkts_acked, s32 rtt)
{
	struct illinois *ca = inet_csk_ca(sk);

	ca->acked = pkts_acked;

	/* dup ack, no rtt sample */
	if (rtt < 0)
		return;

	/* ignore bogus values, this prevents wraparound in alpha math */
	if (rtt > RTT_MAX)
		rtt = RTT_MAX;

	/* keep track of minimum RTT seen so far */
	if (ca->base_rtt > rtt)
		ca->base_rtt = rtt;

	/* and max */
	if (ca->max_rtt < rtt)
		ca->max_rtt = rtt;

	++ca->cnt_rtt;
	ca->sum_rtt += rtt;
}