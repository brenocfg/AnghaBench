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
typedef  char* u_int64_t ;
struct sfb {char* sfb_eff_rate; int /*<<< orphan*/  sfb_qid; int /*<<< orphan*/  sfb_target_qdelay; struct ifnet* sfb_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int cqev_t ;

/* Variables and functions */
#define  CLASSQ_EV_LINK_BANDWIDTH 132 
#define  CLASSQ_EV_LINK_DOWN 131 
#define  CLASSQ_EV_LINK_LATENCY 130 
#define  CLASSQ_EV_LINK_MTU 129 
#define  CLASSQ_EV_LINK_UP 128 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  classq_verbose ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifclassq_calc_target_qdelay (struct ifnet*,int /*<<< orphan*/ *) ; 
 char* ifnet_output_linkrate (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfb_calc_holdtime (struct sfb*,char*) ; 
 int /*<<< orphan*/  sfb_calc_pboxtime (struct sfb*,char*) ; 
 int /*<<< orphan*/  sfb_calc_update_interval (struct sfb*,char*) ; 
 int /*<<< orphan*/  sfb_resetq (struct sfb*,int) ; 

void
sfb_updateq(struct sfb *sp, cqev_t ev)
{
	struct ifnet *ifp = sp->sfb_ifp;

	VERIFY(ifp != NULL);

	switch (ev) {
	case CLASSQ_EV_LINK_BANDWIDTH: {
		u_int64_t eff_rate = ifnet_output_linkrate(ifp);

		/* update parameters only if rate has changed */
		if (eff_rate == sp->sfb_eff_rate)
			break;

		if (classq_verbose) {
			log(LOG_DEBUG, "%s: SFB qid=%d, adapting to new "
			    "eff_rate=%llu bps\n", if_name(ifp), sp->sfb_qid,
			    eff_rate);
		}
		sfb_calc_holdtime(sp, eff_rate);
		sfb_calc_pboxtime(sp, eff_rate);
		ifclassq_calc_target_qdelay(ifp, &sp->sfb_target_qdelay);
		sfb_calc_update_interval(sp, eff_rate);
		break;
	}

	case CLASSQ_EV_LINK_UP:
	case CLASSQ_EV_LINK_DOWN:
		if (classq_verbose) {
			log(LOG_DEBUG, "%s: SFB qid=%d, resetting due to "
			    "link %s\n", if_name(ifp), sp->sfb_qid,
			    (ev == CLASSQ_EV_LINK_UP) ? "UP" : "DOWN");
		}
		sfb_resetq(sp, ev);
		break;

	case CLASSQ_EV_LINK_LATENCY:
	case CLASSQ_EV_LINK_MTU:
	default:
		break;
	}
}