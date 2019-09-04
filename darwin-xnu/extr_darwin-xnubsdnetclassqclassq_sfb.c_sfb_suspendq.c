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
struct sfb {int sfb_flags; int /*<<< orphan*/  sfb_qid; struct ifnet* sfb_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  class_queue_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SFBF_FLOWCTL ; 
 int SFBF_SUSPENDED ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ classq_verbose ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfb_swap_bins (struct sfb*,int /*<<< orphan*/ ) ; 

int
sfb_suspendq(struct sfb *sp, class_queue_t *q, boolean_t on)
{
#pragma unused(q)
	struct ifnet *ifp = sp->sfb_ifp;

	VERIFY(ifp != NULL);

	if ((on && (sp->sfb_flags & SFBF_SUSPENDED)) ||
	    (!on && !(sp->sfb_flags & SFBF_SUSPENDED)))
		return (0);

	if (!(sp->sfb_flags & SFBF_FLOWCTL)) {
		log(LOG_ERR, "%s: SFB qid=%d, unable to %s queue since "
		    "flow-control is not enabled", if_name(ifp), sp->sfb_qid,
		    (on ? "suspend" : "resume"));
		return (ENOTSUP);
	}

	if (classq_verbose) {
		log(LOG_DEBUG, "%s: SFB qid=%d, setting state to %s",
		    if_name(ifp), sp->sfb_qid, (on ? "SUSPENDED" : "RUNNING"));
	}

	if (on) {
		sp->sfb_flags |= SFBF_SUSPENDED;
	} else {
		sp->sfb_flags &= ~SFBF_SUSPENDED;
		sfb_swap_bins(sp, qlen(q));
	}

	return (0);
}