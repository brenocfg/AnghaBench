#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ oseq; int /*<<< orphan*/  bitmap; scalar_t__ seq; } ;
struct TYPE_5__ {scalar_t__ oseq; int /*<<< orphan*/  bitmap; scalar_t__ seq; } ;
struct xfrm_state {int xflags; scalar_t__ replay_maxage; int /*<<< orphan*/  rtimer; TYPE_3__ replay; TYPE_2__ preplay; scalar_t__ replay_maxdiff; } ;
struct xfrm_replay_state {int dummy; } ;
struct TYPE_4__ {int aevent; } ;
struct km_event {TYPE_1__ data; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_MSG_NEWAE ; 
#define  XFRM_REPLAY_TIMEOUT 129 
#define  XFRM_REPLAY_UPDATE 128 
 int XFRM_TIME_DEFER ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void xfrm_replay_notify(struct xfrm_state *x, int event)
{
	struct km_event c;
	/* we send notify messages in case
	 *  1. we updated on of the sequence numbers, and the seqno difference
	 *     is at least x->replay_maxdiff, in this case we also update the
	 *     timeout of our timer function
	 *  2. if x->replay_maxage has elapsed since last update,
	 *     and there were changes
	 *
	 *  The state structure must be locked!
	 */

	switch (event) {
	case XFRM_REPLAY_UPDATE:
		if (x->replay_maxdiff &&
		    (x->replay.seq - x->preplay.seq < x->replay_maxdiff) &&
		    (x->replay.oseq - x->preplay.oseq < x->replay_maxdiff)) {
			if (x->xflags & XFRM_TIME_DEFER)
				event = XFRM_REPLAY_TIMEOUT;
			else
				return;
		}

		break;

	case XFRM_REPLAY_TIMEOUT:
		if ((x->replay.seq == x->preplay.seq) &&
		    (x->replay.bitmap == x->preplay.bitmap) &&
		    (x->replay.oseq == x->preplay.oseq)) {
			x->xflags |= XFRM_TIME_DEFER;
			return;
		}

		break;
	}

	memcpy(&x->preplay, &x->replay, sizeof(struct xfrm_replay_state));
	c.event = XFRM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notify(x, &c);

	if (x->replay_maxage &&
	    !mod_timer(&x->rtimer, jiffies + x->replay_maxage))
		x->xflags &= ~XFRM_TIME_DEFER;
}