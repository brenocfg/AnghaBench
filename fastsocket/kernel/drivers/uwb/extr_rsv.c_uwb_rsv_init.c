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
struct TYPE_5__ {int /*<<< orphan*/  streams; } ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int can_reserve_extra_mases; int window; TYPE_3__ timer; scalar_t__ total_expired; } ;
struct uwb_rc {TYPE_2__ uwb_dev; TYPE_1__ bow; int /*<<< orphan*/  rsv_alien_bp_work; int /*<<< orphan*/  rsv_update_work; int /*<<< orphan*/  rsvs_lock; int /*<<< orphan*/  rsvs_mutex; int /*<<< orphan*/  cnflt_alien_list; int /*<<< orphan*/  reservations; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int UWB_DRP_BACKOFF_WIN_MIN ; 
 int /*<<< orphan*/  UWB_NUM_STREAMS ; 
 int /*<<< orphan*/  bitmap_complement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_alien_bp_work ; 
 int /*<<< orphan*/  uwb_rsv_backoff_win_timer ; 
 int /*<<< orphan*/  uwb_rsv_update_work ; 

void uwb_rsv_init(struct uwb_rc *rc)
{
	INIT_LIST_HEAD(&rc->reservations);
	INIT_LIST_HEAD(&rc->cnflt_alien_list);
	mutex_init(&rc->rsvs_mutex);
	spin_lock_init(&rc->rsvs_lock);
	INIT_DELAYED_WORK(&rc->rsv_update_work, uwb_rsv_update_work);
	INIT_DELAYED_WORK(&rc->rsv_alien_bp_work, uwb_rsv_alien_bp_work);
	rc->bow.can_reserve_extra_mases = true;
	rc->bow.total_expired = 0;
	rc->bow.window = UWB_DRP_BACKOFF_WIN_MIN >> 1;
	init_timer(&rc->bow.timer);
	rc->bow.timer.function = uwb_rsv_backoff_win_timer;
	rc->bow.timer.data     = (unsigned long)&rc->bow;

	bitmap_complement(rc->uwb_dev.streams, rc->uwb_dev.streams, UWB_NUM_STREAMS);
}