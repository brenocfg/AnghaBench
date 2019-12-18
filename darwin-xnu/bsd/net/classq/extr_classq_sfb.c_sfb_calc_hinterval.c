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
typedef  int u_int64_t ;
struct timespec {int dummy; } ;
struct sfb {int /*<<< orphan*/  sfb_nextreset; int /*<<< orphan*/  sfb_hinterval; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 scalar_t__ SFB_HINTERVAL (struct sfb*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int /*<<< orphan*/  net_nsectimer (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_timeradd (struct timespec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sfb_hinterval ; 

__attribute__((used)) static void
sfb_calc_hinterval(struct sfb *sp, u_int64_t *t)
{
	u_int64_t hinterval = 0;
	struct timespec now;

	if (t != NULL) {
		/*
		 * TODO adi@apple.com: use dq_avg to derive hinterval.
		 */
		hinterval = *t;
	}

	if (sfb_hinterval != 0)
		hinterval = sfb_hinterval;
	else if (t == NULL || hinterval == 0)
		hinterval = ((u_int64_t)SFB_HINTERVAL(sp) * NSEC_PER_SEC);

	net_nsectimer(&hinterval, &sp->sfb_hinterval);

	nanouptime(&now);
	net_timeradd(&now, &sp->sfb_hinterval, &sp->sfb_nextreset);
}