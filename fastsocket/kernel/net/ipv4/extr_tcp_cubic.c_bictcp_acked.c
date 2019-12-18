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
typedef  int u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; } ;
struct bictcp {int delayed_ack; int delay_min; scalar_t__ epoch_start; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_RATIO_LIMIT ; 
 int ACK_RATIO_SHIFT ; 
 scalar_t__ HZ ; 
 scalar_t__ TCP_CA_Open ; 
 scalar_t__ USEC_PER_MSEC ; 
 scalar_t__ hystart ; 
 scalar_t__ hystart_low_window ; 
 int /*<<< orphan*/  hystart_update (struct sock*,int) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_time_stamp ; 

__attribute__((used)) static void bictcp_acked(struct sock *sk, u32 cnt, s32 rtt_us)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	const struct tcp_sock *tp = tcp_sk(sk);
	struct bictcp *ca = inet_csk_ca(sk);
	u32 delay;

	if (icsk->icsk_ca_state == TCP_CA_Open) {
		u32 ratio = ca->delayed_ack;

		ratio -= ca->delayed_ack >> ACK_RATIO_SHIFT;
		ratio += cnt;

		ca->delayed_ack = min(ratio, ACK_RATIO_LIMIT);
	}

	/* Some calls are for duplicates without timetamps */
	if (rtt_us < 0)
		return;

	/* Discard delay samples right after fast recovery */
	if ((s32)(tcp_time_stamp - ca->epoch_start) < HZ)
		return;

	delay = (rtt_us << 3) / USEC_PER_MSEC;
	if (delay == 0)
		delay = 1;

	/* first time call or link delay decreases */
	if (ca->delay_min == 0 || ca->delay_min > delay)
		ca->delay_min = delay;

	/* hystart triggers when cwnd is larger than some threshold */
	if (hystart && tp->snd_cwnd <= tp->snd_ssthresh &&
	    tp->snd_cwnd >= hystart_low_window)
		hystart_update(sk, delay);
}