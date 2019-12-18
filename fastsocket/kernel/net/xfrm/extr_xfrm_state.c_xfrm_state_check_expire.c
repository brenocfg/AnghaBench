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
struct TYPE_6__ {scalar_t__ state; int dying; } ;
struct TYPE_5__ {scalar_t__ hard_byte_limit; scalar_t__ hard_packet_limit; scalar_t__ soft_byte_limit; scalar_t__ soft_packet_limit; } ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ packets; scalar_t__ use_time; } ;
struct xfrm_state {TYPE_3__ km; TYPE_2__ lft; TYPE_1__ curlft; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XFRM_STATE_EXPIRED ; 
 scalar_t__ XFRM_STATE_VALID ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  km_state_expired (struct xfrm_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int xfrm_state_check_expire(struct xfrm_state *x)
{
	if (!x->curlft.use_time)
		x->curlft.use_time = get_seconds();

	if (x->km.state != XFRM_STATE_VALID)
		return -EINVAL;

	if (x->curlft.bytes >= x->lft.hard_byte_limit ||
	    x->curlft.packets >= x->lft.hard_packet_limit) {
		x->km.state = XFRM_STATE_EXPIRED;
		mod_timer(&x->timer, jiffies);
		return -EINVAL;
	}

	if (!x->km.dying &&
	    (x->curlft.bytes >= x->lft.soft_byte_limit ||
	     x->curlft.packets >= x->lft.soft_packet_limit)) {
		x->km.dying = 1;
		km_state_expired(x, 0, 0);
	}
	return 0;
}