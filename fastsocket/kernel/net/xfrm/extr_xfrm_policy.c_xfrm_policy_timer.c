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
struct TYPE_6__ {unsigned long add_time; scalar_t__ use_time; } ;
struct TYPE_5__ {long hard_add_expires_seconds; long hard_use_expires_seconds; long soft_add_expires_seconds; long soft_use_expires_seconds; } ;
struct TYPE_4__ {int /*<<< orphan*/  dead; } ;
struct xfrm_policy {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; TYPE_3__ curlft; TYPE_2__ lft; int /*<<< orphan*/  index; TYPE_1__ walk; } ;

/* Variables and functions */
 long LONG_MAX ; 
 long XFRM_KM_TIMEOUT ; 
 unsigned long get_seconds () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  km_policy_expired (struct xfrm_policy*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ make_jiffies (long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_delete (struct xfrm_policy*,int) ; 
 int xfrm_policy_id2dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xfrm_policy_timer(unsigned long data)
{
	struct xfrm_policy *xp = (struct xfrm_policy*)data;
	unsigned long now = get_seconds();
	long next = LONG_MAX;
	int warn = 0;
	int dir;

	read_lock(&xp->lock);

	if (unlikely(xp->walk.dead))
		goto out;

	dir = xfrm_policy_id2dir(xp->index);

	if (xp->lft.hard_add_expires_seconds) {
		long tmo = xp->lft.hard_add_expires_seconds +
			xp->curlft.add_time - now;
		if (tmo <= 0)
			goto expired;
		if (tmo < next)
			next = tmo;
	}
	if (xp->lft.hard_use_expires_seconds) {
		long tmo = xp->lft.hard_use_expires_seconds +
			(xp->curlft.use_time ? : xp->curlft.add_time) - now;
		if (tmo <= 0)
			goto expired;
		if (tmo < next)
			next = tmo;
	}
	if (xp->lft.soft_add_expires_seconds) {
		long tmo = xp->lft.soft_add_expires_seconds +
			xp->curlft.add_time - now;
		if (tmo <= 0) {
			warn = 1;
			tmo = XFRM_KM_TIMEOUT;
		}
		if (tmo < next)
			next = tmo;
	}
	if (xp->lft.soft_use_expires_seconds) {
		long tmo = xp->lft.soft_use_expires_seconds +
			(xp->curlft.use_time ? : xp->curlft.add_time) - now;
		if (tmo <= 0) {
			warn = 1;
			tmo = XFRM_KM_TIMEOUT;
		}
		if (tmo < next)
			next = tmo;
	}

	if (warn)
		km_policy_expired(xp, dir, 0, 0);
	if (next != LONG_MAX &&
	    !mod_timer(&xp->timer, jiffies + make_jiffies(next)))
		xfrm_pol_hold(xp);

out:
	read_unlock(&xp->lock);
	xfrm_pol_put(xp);
	return;

expired:
	read_unlock(&xp->lock);
	if (!xfrm_policy_delete(xp, dir))
		km_policy_expired(xp, dir, 1, 0);
	xfrm_pol_put(xp);
}