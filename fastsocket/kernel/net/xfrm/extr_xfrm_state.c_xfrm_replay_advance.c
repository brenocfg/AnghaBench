#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ seq; scalar_t__ bitmap; } ;
struct TYPE_3__ {scalar_t__ replay_window; } ;
struct xfrm_state {TYPE_2__ replay; TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_REPLAY_UPDATE ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_aevent_is_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_replay_notify (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

void xfrm_replay_advance(struct xfrm_state *x, __be32 net_seq)
{
	u32 diff;
	u32 seq = ntohl(net_seq);

	if (seq > x->replay.seq) {
		diff = seq - x->replay.seq;
		if (diff < x->props.replay_window)
			x->replay.bitmap = ((x->replay.bitmap) << diff) | 1;
		else
			x->replay.bitmap = 1;
		x->replay.seq = seq;
	} else {
		diff = x->replay.seq - seq;
		x->replay.bitmap |= (1U << diff);
	}

	if (xfrm_aevent_is_on(xs_net(x)))
		xfrm_replay_notify(x, XFRM_REPLAY_UPDATE);
}