#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  unsafe_bm; int /*<<< orphan*/  bm; int /*<<< orphan*/  unsafe; int /*<<< orphan*/  safe; } ;
struct TYPE_7__ {int /*<<< orphan*/  unsafe_bm; int /*<<< orphan*/  bm; int /*<<< orphan*/  unsafe; int /*<<< orphan*/  safe; } ;
struct uwb_rsv_move {TYPE_4__ companion_mas; TYPE_1__ final_mas; } ;
struct uwb_rsv {int state; int needs_release_companion_mas; TYPE_3__* rc; TYPE_4__ mas; struct uwb_rsv_move mv; } ;
typedef  enum uwb_rsv_state { ____Placeholder_uwb_rsv_state } uwb_rsv_state ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_2__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_MAS ; 
#define  UWB_RSV_STATE_NONE 141 
#define  UWB_RSV_STATE_O_ESTABLISHED 140 
#define  UWB_RSV_STATE_O_INITIATED 139 
#define  UWB_RSV_STATE_O_MODIFIED 138 
#define  UWB_RSV_STATE_O_MOVE_COMBINING 137 
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 136 
#define  UWB_RSV_STATE_O_MOVE_REDUCING 135 
#define  UWB_RSV_STATE_O_PENDING 134 
#define  UWB_RSV_STATE_T_ACCEPTED 133 
#define  UWB_RSV_STATE_T_CONFLICT 132 
#define  UWB_RSV_STATE_T_DENIED 131 
#define  UWB_RSV_STATE_T_EXPANDING_ACCEPTED 130 
#define  UWB_RSV_STATE_T_PENDING 129 
#define  UWB_RSV_STATE_T_RESIZED 128 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uwb_drp_avail_release (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  uwb_drp_avail_reserve (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  uwb_rsv_callback (struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_dump (char*,struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_state_str (int) ; 
 int /*<<< orphan*/  uwb_rsv_state_update (struct uwb_rsv*,int const) ; 
 int /*<<< orphan*/  uwb_rsv_stroke_timer (struct uwb_rsv*) ; 

void uwb_rsv_set_state(struct uwb_rsv *rsv, enum uwb_rsv_state new_state)
{
	struct uwb_rsv_move *mv = &rsv->mv;

	if (rsv->state == new_state) {
		switch (rsv->state) {
		case UWB_RSV_STATE_O_ESTABLISHED:
		case UWB_RSV_STATE_O_MOVE_EXPANDING:
		case UWB_RSV_STATE_O_MOVE_COMBINING:
		case UWB_RSV_STATE_O_MOVE_REDUCING:
		case UWB_RSV_STATE_T_ACCEPTED:
		case UWB_RSV_STATE_T_EXPANDING_ACCEPTED:
		case UWB_RSV_STATE_T_RESIZED:
		case UWB_RSV_STATE_NONE:
			uwb_rsv_stroke_timer(rsv);
			break;
		default:
			/* Expecting a state transition so leave timer
			   as-is. */
			break;
		}
		return;
	}

	uwb_rsv_dump("SC", rsv);

	switch (new_state) {
	case UWB_RSV_STATE_NONE:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_NONE);
		uwb_rsv_callback(rsv);
		break;
	case UWB_RSV_STATE_O_INITIATED:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_INITIATED);
		break;
	case UWB_RSV_STATE_O_PENDING:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_PENDING);
		break;
	case UWB_RSV_STATE_O_MODIFIED:
		/* in the companion there are the MASes to drop */
		bitmap_andnot(rsv->mas.bm, rsv->mas.bm, mv->companion_mas.bm, UWB_NUM_MAS);
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_MODIFIED);
		break;
	case UWB_RSV_STATE_O_ESTABLISHED:
		if (rsv->state == UWB_RSV_STATE_O_MODIFIED
		    || rsv->state == UWB_RSV_STATE_O_MOVE_REDUCING) {
			uwb_drp_avail_release(rsv->rc, &mv->companion_mas);
			rsv->needs_release_companion_mas = false;
		}
		uwb_drp_avail_reserve(rsv->rc, &rsv->mas);
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_ESTABLISHED);
		uwb_rsv_callback(rsv);
		break;
	case UWB_RSV_STATE_O_MOVE_EXPANDING:
		rsv->needs_release_companion_mas = true;
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_MOVE_EXPANDING);
		break;
	case UWB_RSV_STATE_O_MOVE_COMBINING:
		rsv->needs_release_companion_mas = false;
		uwb_drp_avail_reserve(rsv->rc, &mv->companion_mas);
		bitmap_or(rsv->mas.bm, rsv->mas.bm, mv->companion_mas.bm, UWB_NUM_MAS);
		rsv->mas.safe   += mv->companion_mas.safe;
		rsv->mas.unsafe += mv->companion_mas.unsafe;
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_MOVE_COMBINING);
		break;
	case UWB_RSV_STATE_O_MOVE_REDUCING:
		bitmap_andnot(mv->companion_mas.bm, rsv->mas.bm, mv->final_mas.bm, UWB_NUM_MAS);
		rsv->needs_release_companion_mas = true;
		rsv->mas.safe   = mv->final_mas.safe;
		rsv->mas.unsafe = mv->final_mas.unsafe;
		bitmap_copy(rsv->mas.bm, mv->final_mas.bm, UWB_NUM_MAS);
		bitmap_copy(rsv->mas.unsafe_bm, mv->final_mas.unsafe_bm, UWB_NUM_MAS);
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_O_MOVE_REDUCING);
		break;
	case UWB_RSV_STATE_T_ACCEPTED:
	case UWB_RSV_STATE_T_RESIZED:
		rsv->needs_release_companion_mas = false;
		uwb_drp_avail_reserve(rsv->rc, &rsv->mas);
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_T_ACCEPTED);
		uwb_rsv_callback(rsv);
		break;
	case UWB_RSV_STATE_T_DENIED:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_T_DENIED);
		break;
	case UWB_RSV_STATE_T_CONFLICT:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_T_CONFLICT);
		break;
	case UWB_RSV_STATE_T_PENDING:
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_T_PENDING);
		break;
	case UWB_RSV_STATE_T_EXPANDING_ACCEPTED:
		rsv->needs_release_companion_mas = true;
		uwb_drp_avail_reserve(rsv->rc, &mv->companion_mas);
		uwb_rsv_state_update(rsv, UWB_RSV_STATE_T_EXPANDING_ACCEPTED);
		break;
	default:
		dev_err(&rsv->rc->uwb_dev.dev, "unhandled state: %s (%d)\n",
			uwb_rsv_state_str(new_state), new_state);
	}
}