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
struct tcp_timewait_sock {scalar_t__ tw_ts_recent_stamp; scalar_t__ tw_ts_recent; } ;
struct sock {int dummy; } ;
struct inet_timewait_sock {int /*<<< orphan*/  tw_daddr; } ;
struct inet_peer {scalar_t__ tcp_ts_stamp; scalar_t__ tcp_ts; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ TCP_PAWS_MSL ; 
 scalar_t__ get_seconds () ; 
 struct inet_peer* inet_getpeer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet_putpeer (struct inet_peer*) ; 
 struct tcp_timewait_sock* tcp_twsk (struct sock*) ; 

int tcp_v4_tw_remember_stamp(struct inet_timewait_sock *tw)
{
	struct inet_peer *peer = inet_getpeer(tw->tw_daddr, 1);

	if (peer) {
		const struct tcp_timewait_sock *tcptw = tcp_twsk((struct sock *)tw);

		if ((s32)(peer->tcp_ts - tcptw->tw_ts_recent) <= 0 ||
		    (peer->tcp_ts_stamp + TCP_PAWS_MSL < get_seconds() &&
		     peer->tcp_ts_stamp <= tcptw->tw_ts_recent_stamp)) {
			peer->tcp_ts_stamp = tcptw->tw_ts_recent_stamp;
			peer->tcp_ts	   = tcptw->tw_ts_recent;
		}
		inet_putpeer(peer);
		return 1;
	}

	return 0;
}