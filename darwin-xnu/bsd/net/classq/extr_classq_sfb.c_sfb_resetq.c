#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_9__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; } ;
struct sfb {int sfb_allocation; int sfb_qlim; int sfb_drop_thresh; int /*<<< orphan*/  sfb_flags; TYPE_4__ sfb_update_interval; scalar_t__ sfb_target_qdelay; TYPE_3__ sfb_hinterval; TYPE_2__ sfb_pboxtime; TYPE_1__ sfb_holdtime; int /*<<< orphan*/  sfb_qid; TYPE_5__* sfb_stats; TYPE_5__** sfb_bins; int /*<<< orphan*/  sfb_eff_rate; scalar_t__ sfb_current; scalar_t__ sfb_clearpkts; struct ifnet* sfb_ifp; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ cqev_t ;
struct TYPE_10__ {void* fudge; } ;

/* Variables and functions */
 scalar_t__ CLASSQ_EV_LINK_DOWN ; 
 scalar_t__ CLASSQ_EV_LINK_UP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_5__**,int) ; 
 int /*<<< orphan*/  classq_verbose ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifclassq_calc_target_qdelay (struct ifnet*,scalar_t__*) ; 
 int /*<<< orphan*/  ifnet_output_linkrate (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sfb_allocation ; 
 int /*<<< orphan*/  sfb_calc_hinterval (struct sfb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfb_calc_holdtime (struct sfb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_calc_pboxtime (struct sfb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_calc_update_interval (struct sfb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_fclists_clean (struct sfb*) ; 
 void* sfb_random (struct sfb*) ; 

__attribute__((used)) static void
sfb_resetq(struct sfb *sp, cqev_t ev)
{
	struct ifnet *ifp = sp->sfb_ifp;
	u_int64_t eff_rate;

	VERIFY(ifp != NULL);

	if (ev != CLASSQ_EV_LINK_DOWN) {
		(*sp->sfb_bins)[0].fudge = sfb_random(sp);
		(*sp->sfb_bins)[1].fudge = sfb_random(sp);
		sp->sfb_allocation = ((sfb_allocation == 0) ?
		    (sp->sfb_qlim / 3) : sfb_allocation);
		sp->sfb_drop_thresh = sp->sfb_allocation +
		    (sp->sfb_allocation >> 1);
	}

	sp->sfb_clearpkts = 0;
	sp->sfb_current = 0;

	eff_rate = ifnet_output_linkrate(ifp);
	sp->sfb_eff_rate = eff_rate;

	sfb_calc_holdtime(sp, eff_rate);
	sfb_calc_pboxtime(sp, eff_rate);
	sfb_calc_hinterval(sp, NULL);
	ifclassq_calc_target_qdelay(ifp, &sp->sfb_target_qdelay);
	sfb_calc_update_interval(sp, eff_rate);

	if (ev == CLASSQ_EV_LINK_DOWN ||
	    ev == CLASSQ_EV_LINK_UP)
		sfb_fclists_clean(sp);

	bzero(sp->sfb_bins, sizeof (*sp->sfb_bins));
	bzero(&sp->sfb_stats, sizeof (sp->sfb_stats));

	if (ev == CLASSQ_EV_LINK_DOWN || !classq_verbose)
		return;

	log(LOG_DEBUG, "%s: SFB qid=%d, holdtime=%llu nsec, "
	    "pboxtime=%llu nsec, allocation=%d, drop_thresh=%d, "
	    "hinterval=%d sec, sfb_bins=%d bytes, eff_rate=%llu bps"
	    "target_qdelay= %llu nsec "
	    "update_interval=%llu sec %llu nsec flags=0x%x\n",
	    if_name(ifp), sp->sfb_qid, (u_int64_t)sp->sfb_holdtime.tv_nsec,
	    (u_int64_t)sp->sfb_pboxtime.tv_nsec,
	    (u_int32_t)sp->sfb_allocation, (u_int32_t)sp->sfb_drop_thresh,
	    (int)sp->sfb_hinterval.tv_sec, (int)sizeof (*sp->sfb_bins),
	    eff_rate, (u_int64_t)sp->sfb_target_qdelay,
	    (u_int64_t)sp->sfb_update_interval.tv_sec,
	    (u_int64_t)sp->sfb_update_interval.tv_nsec, sp->sfb_flags);
}