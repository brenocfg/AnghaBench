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
struct TYPE_4__ {int /*<<< orphan*/  rehash_intval; int /*<<< orphan*/  pbox_time; int /*<<< orphan*/  hold_time; } ;
struct sfb_stats {TYPE_3__* binstats; TYPE_1__ sfbstats; int /*<<< orphan*/  update_interval; int /*<<< orphan*/  flags; int /*<<< orphan*/  delay_fcthreshold; int /*<<< orphan*/  min_estdelay; int /*<<< orphan*/  target_qdelay; int /*<<< orphan*/  current; int /*<<< orphan*/  clearpkts; int /*<<< orphan*/  dropthresh; int /*<<< orphan*/  allocation; } ;
struct sfb {TYPE_2__** sfb_bins; TYPE_1__ sfb_stats; int /*<<< orphan*/  sfb_update_interval; int /*<<< orphan*/  sfb_hinterval; int /*<<< orphan*/  sfb_pboxtime; int /*<<< orphan*/  sfb_holdtime; int /*<<< orphan*/  sfb_flags; int /*<<< orphan*/  sfb_fc_threshold; int /*<<< orphan*/  sfb_min_qdelay; int /*<<< orphan*/  sfb_target_qdelay; int /*<<< orphan*/  sfb_current; int /*<<< orphan*/  sfb_clearpkts; int /*<<< orphan*/  sfb_drop_thresh; int /*<<< orphan*/  sfb_allocation; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CASSERT (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_timernsec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sfb_getstats(struct sfb *sp, struct sfb_stats *sps)
{
	sps->allocation = sp->sfb_allocation;
	sps->dropthresh = sp->sfb_drop_thresh;
	sps->clearpkts = sp->sfb_clearpkts;
	sps->current = sp->sfb_current;
	sps->target_qdelay = sp->sfb_target_qdelay;
	sps->min_estdelay = sp->sfb_min_qdelay;
	sps->delay_fcthreshold = sp->sfb_fc_threshold;
	sps->flags = sp->sfb_flags;

	net_timernsec(&sp->sfb_holdtime, &sp->sfb_stats.hold_time);
	net_timernsec(&sp->sfb_pboxtime, &sp->sfb_stats.pbox_time);
	net_timernsec(&sp->sfb_hinterval, &sp->sfb_stats.rehash_intval);
	net_timernsec(&sp->sfb_update_interval, &sps->update_interval);
	*(&(sps->sfbstats)) = *(&(sp->sfb_stats));

	_CASSERT(sizeof ((*sp->sfb_bins)[0].stats) ==
	    sizeof (sps->binstats[0].stats));

	bcopy(&(*sp->sfb_bins)[0].stats, &sps->binstats[0].stats,
	    sizeof (sps->binstats[0].stats));
	bcopy(&(*sp->sfb_bins)[1].stats, &sps->binstats[1].stats,
	    sizeof (sps->binstats[1].stats));
}