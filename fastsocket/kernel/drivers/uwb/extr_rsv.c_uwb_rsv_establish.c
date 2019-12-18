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
struct uwb_rsv {int tiebreaker; int /*<<< orphan*/ * owner; int /*<<< orphan*/  rc_node; int /*<<< orphan*/  mas; struct uwb_rc* rc; } ;
struct uwb_rc {int /*<<< orphan*/  rsvs_mutex; int /*<<< orphan*/  uwb_dev; int /*<<< orphan*/  reservations; } ;
struct uwb_mas_bm {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int UWB_RSV_ALLOC_NOT_FOUND ; 
 int /*<<< orphan*/  UWB_RSV_STATE_O_INITIATED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int random32 () ; 
 int /*<<< orphan*/  uwb_dev_get (int /*<<< orphan*/ *) ; 
 int uwb_drp_avail_reserve_pending (struct uwb_rc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_drp_available (struct uwb_rc*,struct uwb_mas_bm*) ; 
 int uwb_rsv_find_best_allocation (struct uwb_rsv*,struct uwb_mas_bm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_get (struct uwb_rsv*) ; 
 int uwb_rsv_get_stream (struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_put_stream (struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,int /*<<< orphan*/ ) ; 

int uwb_rsv_establish(struct uwb_rsv *rsv)
{
	struct uwb_rc *rc = rsv->rc;
	struct uwb_mas_bm available;
	int ret;

	mutex_lock(&rc->rsvs_mutex);
	ret = uwb_rsv_get_stream(rsv);
	if (ret)
		goto out;

	rsv->tiebreaker = random32() & 1;
	/* get available mas bitmap */
	uwb_drp_available(rc, &available);

	ret = uwb_rsv_find_best_allocation(rsv, &available, &rsv->mas);
	if (ret == UWB_RSV_ALLOC_NOT_FOUND) {
		ret = -EBUSY;
		uwb_rsv_put_stream(rsv);
		goto out;
	}

	ret = uwb_drp_avail_reserve_pending(rc, &rsv->mas);
	if (ret != 0) {
		uwb_rsv_put_stream(rsv);
		goto out;
	}

	uwb_rsv_get(rsv);
	list_add_tail(&rsv->rc_node, &rc->reservations);
	rsv->owner = &rc->uwb_dev;
	uwb_dev_get(rsv->owner);
	uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_INITIATED);
out:
	mutex_unlock(&rc->rsvs_mutex);
	return ret;
}