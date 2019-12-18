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
typedef  scalar_t__ u_int32_t ;
struct sfb {int sfb_flags; scalar_t__ sfb_qid; scalar_t__ sfb_qlim; struct ifnet* sfb_ifp; struct sfb* sfb_fc_lists; struct sfb* sfb_bins; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fclist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_EV_INIT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SFBF_ECN ; 
 scalar_t__ SFBF_USERFLAGS ; 
 int SFB_BINS ; 
 TYPE_1__* SFB_FC_LIST (struct sfb*,int) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct sfb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sfb_bins_size ; 
 int /*<<< orphan*/  sfb_bins_zone ; 
 int /*<<< orphan*/  sfb_destroy (struct sfb*) ; 
 int /*<<< orphan*/  sfb_fcl_size ; 
 int /*<<< orphan*/  sfb_fcl_zone ; 
 int /*<<< orphan*/  sfb_resetq (struct sfb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_size ; 
 int /*<<< orphan*/  sfb_zone ; 
 void* zalloc (int /*<<< orphan*/ ) ; 

struct sfb *
sfb_alloc(struct ifnet *ifp, u_int32_t qid, u_int32_t qlim, u_int32_t flags)
{
	struct sfb *sp;
	int i;

	VERIFY(ifp != NULL && qlim > 0);

	sp = zalloc(sfb_zone);
	if (sp == NULL) {
		log(LOG_ERR, "%s: SFB unable to allocate\n", if_name(ifp));
		return (NULL);
	}
	bzero(sp, sfb_size);

	if ((sp->sfb_bins = zalloc(sfb_bins_zone)) == NULL) {
		log(LOG_ERR, "%s: SFB unable to allocate bins\n", if_name(ifp));
		sfb_destroy(sp);
		return (NULL);
	}
	bzero(sp->sfb_bins, sfb_bins_size);

	if ((sp->sfb_fc_lists = zalloc(sfb_fcl_zone)) == NULL) {
		log(LOG_ERR, "%s: SFB unable to allocate flow control lists\n",
		    if_name(ifp));
		sfb_destroy(sp);
		return (NULL);
	}
	bzero(sp->sfb_fc_lists, sfb_fcl_size);

	for (i = 0; i < SFB_BINS; ++i)
		STAILQ_INIT(&SFB_FC_LIST(sp, i)->fclist);

	sp->sfb_ifp = ifp;
	sp->sfb_qlim = qlim;
	sp->sfb_qid = qid;
	sp->sfb_flags = (flags & SFBF_USERFLAGS);
#if !PF_ECN
	if (sp->sfb_flags & SFBF_ECN) {
		sp->sfb_flags &= ~SFBF_ECN;
		log(LOG_ERR, "%s: SFB qid=%d, ECN not available; ignoring "
		    "SFBF_ECN flag!\n", if_name(ifp), sp->sfb_qid);
	}
#endif /* !PF_ECN */

	sfb_resetq(sp, CLASSQ_EV_INIT);

	return (sp);
}