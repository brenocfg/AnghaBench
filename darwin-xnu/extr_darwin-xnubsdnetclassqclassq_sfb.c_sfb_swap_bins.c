#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct sfbbinstats {scalar_t__ pmark; scalar_t__ bytes; scalar_t__ pkts; } ;
struct sfb_fcl {int /*<<< orphan*/  fclist; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_rehash; } ;
struct sfb {int sfb_flags; int sfb_current; TYPE_2__** sfb_bins; int /*<<< orphan*/  sfb_qid; int /*<<< orphan*/  sfb_ifp; TYPE_1__ sfb_stats; int /*<<< orphan*/  sfb_clearpkts; } ;
struct TYPE_4__ {int /*<<< orphan*/  freezetime; int /*<<< orphan*/  fudge; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int SFBF_SUSPENDED ; 
 int SFB_BINS ; 
 struct sfbbinstats* SFB_BINST (struct sfb*,int,int,int) ; 
 struct sfb_fcl* SFB_FC_LIST (struct sfb*,int) ; 
 int SFB_LEVELS ; 
 scalar_t__ SFB_MAX_PMARK ; 
 scalar_t__ SFB_PMARK_WARM ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ classq_verbose ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_fclist_append (struct sfb*,struct sfb_fcl*) ; 
 int /*<<< orphan*/  sfb_random (struct sfb*) ; 

__attribute__((used)) static void
sfb_swap_bins(struct sfb *sp, u_int32_t len)
{
	int i, j, s;

	if (sp->sfb_flags & SFBF_SUSPENDED)
		return;

	s = sp->sfb_current;
	VERIFY((s + (s ^ 1)) == 1);

	(*sp->sfb_bins)[s].fudge = sfb_random(sp); /* recompute perturbation */
	sp->sfb_clearpkts = len;
	sp->sfb_stats.num_rehash++;

	s = (sp->sfb_current ^= 1);	/* flip the bit (swap current) */

	if (classq_verbose) {
		log(LOG_DEBUG, "%s: SFB qid=%d, set %d is now current, "
		    "qlen=%d\n", if_name(sp->sfb_ifp), sp->sfb_qid, s, len);
	}

	/* clear freezetime for all current bins */
	bzero(&(*sp->sfb_bins)[s].freezetime,
	    sizeof ((*sp->sfb_bins)[s].freezetime));

	/* clear/adjust bin statistics and flow control lists */
	for (i = 0; i < SFB_BINS; i++) {
		struct sfb_fcl *fcl = SFB_FC_LIST(sp, i);

		if (!STAILQ_EMPTY(&fcl->fclist))
			sfb_fclist_append(sp, fcl);

		for (j = 0; j < SFB_LEVELS; j++) {
			struct sfbbinstats *cbin, *wbin;

			cbin = SFB_BINST(sp, j, i, s);		/* current */
			wbin = SFB_BINST(sp, j, i, s ^ 1);	/* warm-up */

			cbin->pkts = 0;
			cbin->bytes = 0;
			if (cbin->pmark > SFB_MAX_PMARK)
				cbin->pmark = SFB_MAX_PMARK;
			if (cbin->pmark < 0)
				cbin->pmark = 0;

			/*
			 * Keep pmark from before to identify
			 * non-responsives immediately.
			 */
			if (wbin->pmark > SFB_PMARK_WARM)
				wbin->pmark = SFB_PMARK_WARM;
		}
	}
}