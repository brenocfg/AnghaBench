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
struct tcpcb {int t_srtt; scalar_t__ t_rxtshift; } ;
struct mptsub {int /*<<< orphan*/  mpts_socket; } ;

/* Variables and functions */
 struct tcpcb* sototcpcb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mptsub *
mptcp_choose_subflow(struct mptsub *mpts, struct mptsub *curbest, int *currtt)
{
	struct tcpcb *tp = sototcpcb(mpts->mpts_socket);

	/*
	 * Lower RTT? Take it, if it's our first one, or
	 * it doesn't has any loss, or the current one has
	 * loss as well.
	 */
	if (tp->t_srtt && *currtt > tp->t_srtt &&
	    (curbest == NULL || tp->t_rxtshift == 0 ||
	     sototcpcb(curbest->mpts_socket)->t_rxtshift)) {
		*currtt = tp->t_srtt;
		return (mpts);
	}

	/*
	 * If we find a subflow without loss, take it always!
	 */
	if (curbest &&
	    sototcpcb(curbest->mpts_socket)->t_rxtshift &&
	    tp->t_rxtshift == 0) {
		*currtt = tp->t_srtt;
		return (mpts);
	}

	return (curbest != NULL ? curbest : mpts);
}