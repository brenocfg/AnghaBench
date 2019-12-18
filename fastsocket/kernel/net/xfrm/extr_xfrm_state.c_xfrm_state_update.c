#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ use_time; } ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ dying; } ;
struct TYPE_6__ {int /*<<< orphan*/  family; } ;
struct TYPE_5__ {int /*<<< orphan*/  proto; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_4__ curlft; int /*<<< orphan*/  timer; TYPE_3__ km; int /*<<< orphan*/  lft; int /*<<< orphan*/  sel; int /*<<< orphan*/ * coaddr; int /*<<< orphan*/ * encap; TYPE_2__ props; TYPE_1__ id; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
 scalar_t__ XFRM_STATE_ACQ ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  __xfrm_state_insert (struct xfrm_state*) ; 
 struct xfrm_state* __xfrm_state_locate (struct xfrm_state*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int xfrm_id_proto_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_check_expire (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_delete (struct xfrm_state*) ; 
 scalar_t__ xfrm_state_kern (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_lock ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

int xfrm_state_update(struct xfrm_state *x)
{
	struct xfrm_state *x1, *to_put;
	int err;
	int use_spi = xfrm_id_proto_match(x->id.proto, IPSEC_PROTO_ANY);

	to_put = NULL;

	spin_lock_bh(&xfrm_state_lock);
	x1 = __xfrm_state_locate(x, use_spi, x->props.family);

	err = -ESRCH;
	if (!x1)
		goto out;

	if (xfrm_state_kern(x1)) {
		to_put = x1;
		err = -EEXIST;
		goto out;
	}

	if (x1->km.state == XFRM_STATE_ACQ) {
		__xfrm_state_insert(x);
		x = NULL;
	}
	err = 0;

out:
	spin_unlock_bh(&xfrm_state_lock);

	if (to_put)
		xfrm_state_put(to_put);

	if (err)
		return err;

	if (!x) {
		xfrm_state_delete(x1);
		xfrm_state_put(x1);
		return 0;
	}

	err = -EINVAL;
	spin_lock_bh(&x1->lock);
	if (likely(x1->km.state == XFRM_STATE_VALID)) {
		if (x->encap && x1->encap)
			memcpy(x1->encap, x->encap, sizeof(*x1->encap));
		if (x->coaddr && x1->coaddr) {
			memcpy(x1->coaddr, x->coaddr, sizeof(*x1->coaddr));
		}
		if (!use_spi && memcmp(&x1->sel, &x->sel, sizeof(x1->sel)))
			memcpy(&x1->sel, &x->sel, sizeof(x1->sel));
		memcpy(&x1->lft, &x->lft, sizeof(x1->lft));
		x1->km.dying = 0;

		mod_timer(&x1->timer, jiffies + HZ);
		if (x1->curlft.use_time)
			xfrm_state_check_expire(x1);

		err = 0;
	}
	spin_unlock_bh(&x1->lock);

	xfrm_state_put(x1);

	return err;
}