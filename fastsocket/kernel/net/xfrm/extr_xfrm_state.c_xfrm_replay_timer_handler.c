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
struct TYPE_2__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  xflags; TYPE_1__ km; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_REPLAY_TIMEOUT ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  XFRM_TIME_DEFER ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm_aevent_is_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_replay_notify (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void xfrm_replay_timer_handler(unsigned long data)
{
	struct xfrm_state *x = (struct xfrm_state*)data;

	spin_lock(&x->lock);

	if (x->km.state == XFRM_STATE_VALID) {
		if (xfrm_aevent_is_on(xs_net(x)))
			xfrm_replay_notify(x, XFRM_REPLAY_TIMEOUT);
		else
			x->xflags |= XFRM_TIME_DEFER;
	}

	spin_unlock(&x->lock);
}