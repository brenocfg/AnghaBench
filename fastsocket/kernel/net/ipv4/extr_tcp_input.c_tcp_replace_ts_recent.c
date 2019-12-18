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
struct TYPE_2__ {scalar_t__ saw_tstamp; } ;
struct tcp_sock {TYPE_1__ rx_opt; int /*<<< orphan*/  rcv_wup; } ;

/* Variables and functions */
 int /*<<< orphan*/  after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_paws_check (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_store_ts_recent (struct tcp_sock*) ; 

__attribute__((used)) static inline void tcp_replace_ts_recent(struct tcp_sock *tp, u32 seq)
{
	if (tp->rx_opt.saw_tstamp && !after(seq, tp->rcv_wup)) {
		/* PAWS bug workaround wrt. ACK frames, the PAWS discard
		 * extra check below makes sure this can only happen
		 * for pure ACK frames.  -DaveM
		 *
		 * Not only, also it occurs for expired timestamps.
		 */

		if (tcp_paws_check(&tp->rx_opt, 0))
			tcp_store_ts_recent(tp);
	}
}