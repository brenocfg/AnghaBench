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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd_stamp; int /*<<< orphan*/  snd_cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tcp_max_burst (struct tcp_sock*) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 

__attribute__((used)) static inline void tcp_moderate_cwnd(struct tcp_sock *tp)
{
	tp->snd_cwnd = min(tp->snd_cwnd,
			   tcp_packets_in_flight(tp) + tcp_max_burst(tp));
	tp->snd_cwnd_stamp = tcp_time_stamp;
}