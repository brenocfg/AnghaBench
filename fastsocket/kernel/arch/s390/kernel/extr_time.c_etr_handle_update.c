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
struct etr_eacr {int dp; scalar_t__ p1; scalar_t__ p0; int /*<<< orphan*/  es; int /*<<< orphan*/  e1; int /*<<< orphan*/  e0; } ;
struct TYPE_2__ {scalar_t__ q; } ;
struct etr_aib {TYPE_1__ esw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETR_STEAI_PORT_0 ; 
 int /*<<< orphan*/  ETR_STEAI_PORT_1 ; 
 int /*<<< orphan*/  check_sync_clock () ; 
 struct etr_aib etr_port0 ; 
 scalar_t__ etr_port0_online ; 
 int etr_port0_uptodate ; 
 struct etr_aib etr_port1 ; 
 int etr_port1_uptodate ; 
 scalar_t__ etr_steai_available ; 
 int /*<<< orphan*/  etr_steai_cv (struct etr_aib*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct etr_eacr etr_handle_update(struct etr_aib *aib,
					 struct etr_eacr eacr)
{
	/* With both ports disabled the aib information is useless. */
	if (!eacr.e0 && !eacr.e1)
		return eacr;

	/* Update port0 or port1 with aib stored in etr_work_fn. */
	if (aib->esw.q == 0) {
		/* Information for port 0 stored. */
		if (eacr.p0 && !etr_port0_uptodate) {
			etr_port0 = *aib;
			if (etr_port0_online)
				etr_port0_uptodate = 1;
		}
	} else {
		/* Information for port 1 stored. */
		if (eacr.p1 && !etr_port1_uptodate) {
			etr_port1 = *aib;
			if (etr_port0_online)
				etr_port1_uptodate = 1;
		}
	}

	/*
	 * Do not try to get the alternate port aib if the clock
	 * is not in sync yet.
	 */
	if (!eacr.es || !check_sync_clock())
		return eacr;

	/*
	 * If steai is available we can get the information about
	 * the other port immediately. If only stetr is available the
	 * data-port bit toggle has to be used.
	 */
	if (etr_steai_available) {
		if (eacr.p0 && !etr_port0_uptodate) {
			etr_steai_cv(&etr_port0, ETR_STEAI_PORT_0);
			etr_port0_uptodate = 1;
		}
		if (eacr.p1 && !etr_port1_uptodate) {
			etr_steai_cv(&etr_port1, ETR_STEAI_PORT_1);
			etr_port1_uptodate = 1;
		}
	} else {
		/*
		 * One port was updated above, if the other
		 * port is not uptodate toggle dp bit.
		 */
		if ((eacr.p0 && !etr_port0_uptodate) ||
		    (eacr.p1 && !etr_port1_uptodate))
			eacr.dp ^= 1;
		else
			eacr.dp = 0;
	}
	return eacr;
}