#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct etr_eacr {int ea; int dp; int es; int sl; int e0; int e1; scalar_t__ p1; scalar_t__ p0; } ;
struct TYPE_7__ {scalar_t__ psc0; scalar_t__ psc1; } ;
struct etr_aib {TYPE_1__ esw; } ;
struct TYPE_8__ {TYPE_1__ esw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ check_sync_clock () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_sync_clock ; 
 scalar_t__ etr_compare_network (TYPE_2__*,TYPE_2__*) ; 
 struct etr_eacr etr_eacr ; 
 struct etr_eacr etr_handle_events (struct etr_eacr) ; 
 struct etr_eacr etr_handle_update (struct etr_aib*,struct etr_eacr) ; 
 scalar_t__ etr_lpsc_operational_alt ; 
 scalar_t__ etr_lpsc_operational_step ; 
 scalar_t__ etr_lpsc_pps_mode ; 
 int /*<<< orphan*/  etr_mode_is_etr (struct etr_eacr) ; 
 int /*<<< orphan*/  etr_mode_is_pps (struct etr_eacr) ; 
 TYPE_2__ etr_port0 ; 
 scalar_t__ etr_port0_uptodate ; 
 TYPE_2__ etr_port1 ; 
 scalar_t__ etr_port1_uptodate ; 
 scalar_t__ etr_port_valid (TYPE_2__*,int) ; 
 int /*<<< orphan*/  etr_set_sync_timeout () ; 
 int /*<<< orphan*/  etr_set_tolec_timeout (unsigned long long) ; 
 scalar_t__ etr_stetr (struct etr_aib*) ; 
 scalar_t__ etr_sync_clock_stop (struct etr_aib*,int) ; 
 int /*<<< orphan*/  etr_timer ; 
 int etr_tolec ; 
 int /*<<< orphan*/  etr_update_eacr (struct etr_eacr) ; 
 int /*<<< orphan*/  etr_work_mutex ; 
 unsigned long long get_clock () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void etr_work_fn(struct work_struct *work)
{
	unsigned long long now;
	struct etr_eacr eacr;
	struct etr_aib aib;
	int sync_port;

	/* prevent multiple execution. */
	mutex_lock(&etr_work_mutex);

	/* Create working copy of etr_eacr. */
	eacr = etr_eacr;

	/* Check for the different events and their immediate effects. */
	eacr = etr_handle_events(eacr);

	/* Check if ETR is supposed to be active. */
	eacr.ea = eacr.p0 || eacr.p1;
	if (!eacr.ea) {
		/* Both ports offline. Reset everything. */
		eacr.dp = eacr.es = eacr.sl = 0;
		on_each_cpu(disable_sync_clock, NULL, 1);
		del_timer_sync(&etr_timer);
		etr_update_eacr(eacr);
		goto out_unlock;
	}

	/* Store aib to get the current ETR status word. */
	BUG_ON(etr_stetr(&aib) != 0);
	etr_port0.esw = etr_port1.esw = aib.esw;	/* Copy status word. */
	now = get_clock();

	/*
	 * Update the port information if the last stepping port change
	 * or data port change is older than 1.6 seconds.
	 */
	if (now >= etr_tolec + (1600000 << 12))
		eacr = etr_handle_update(&aib, eacr);

	/*
	 * Select ports to enable. The prefered synchronization mode is PPS.
	 * If a port can be enabled depends on a number of things:
	 * 1) The port needs to be online and uptodate. A port is not
	 *    disabled just because it is not uptodate, but it is only
	 *    enabled if it is uptodate.
	 * 2) The port needs to have the same mode (pps / etr).
	 * 3) The port needs to be usable -> etr_port_valid() == 1
	 * 4) To enable the second port the clock needs to be in sync.
	 * 5) If both ports are useable and are ETR ports, the network id
	 *    has to be the same.
	 * The eacr.sl bit is used to indicate etr mode vs. pps mode.
	 */
	if (eacr.p0 && aib.esw.psc0 == etr_lpsc_pps_mode) {
		eacr.sl = 0;
		eacr.e0 = 1;
		if (!etr_mode_is_pps(etr_eacr))
			eacr.es = 0;
		if (!eacr.es || !eacr.p1 || aib.esw.psc1 != etr_lpsc_pps_mode)
			eacr.e1 = 0;
		// FIXME: uptodate checks ?
		else if (etr_port0_uptodate && etr_port1_uptodate)
			eacr.e1 = 1;
		sync_port = (etr_port0_uptodate &&
			     etr_port_valid(&etr_port0, 0)) ? 0 : -1;
	} else if (eacr.p1 && aib.esw.psc1 == etr_lpsc_pps_mode) {
		eacr.sl = 0;
		eacr.e0 = 0;
		eacr.e1 = 1;
		if (!etr_mode_is_pps(etr_eacr))
			eacr.es = 0;
		sync_port = (etr_port1_uptodate &&
			     etr_port_valid(&etr_port1, 1)) ? 1 : -1;
	} else if (eacr.p0 && aib.esw.psc0 == etr_lpsc_operational_step) {
		eacr.sl = 1;
		eacr.e0 = 1;
		if (!etr_mode_is_etr(etr_eacr))
			eacr.es = 0;
		if (!eacr.es || !eacr.p1 ||
		    aib.esw.psc1 != etr_lpsc_operational_alt)
			eacr.e1 = 0;
		else if (etr_port0_uptodate && etr_port1_uptodate &&
			 etr_compare_network(&etr_port0, &etr_port1))
			eacr.e1 = 1;
		sync_port = (etr_port0_uptodate &&
			     etr_port_valid(&etr_port0, 0)) ? 0 : -1;
	} else if (eacr.p1 && aib.esw.psc1 == etr_lpsc_operational_step) {
		eacr.sl = 1;
		eacr.e0 = 0;
		eacr.e1 = 1;
		if (!etr_mode_is_etr(etr_eacr))
			eacr.es = 0;
		sync_port = (etr_port1_uptodate &&
			     etr_port_valid(&etr_port1, 1)) ? 1 : -1;
	} else {
		/* Both ports not usable. */
		eacr.es = eacr.sl = 0;
		sync_port = -1;
	}

	/*
	 * If the clock is in sync just update the eacr and return.
	 * If there is no valid sync port wait for a port update.
	 */
	if ((eacr.es && check_sync_clock()) || sync_port < 0) {
		etr_update_eacr(eacr);
		etr_set_tolec_timeout(now);
		goto out_unlock;
	}

	/*
	 * Prepare control register for clock syncing
	 * (reset data port bit, set sync check control.
	 */
	eacr.dp = 0;
	eacr.es = 1;

	/*
	 * Update eacr and try to synchronize the clock. If the update
	 * of eacr caused a stepping port switch (or if we have to
	 * assume that a stepping port switch has occured) or the
	 * clock syncing failed, reset the sync check control bit
	 * and set up a timer to try again after 0.5 seconds
	 */
	etr_update_eacr(eacr);
	if (now < etr_tolec + (1600000 << 12) ||
	    etr_sync_clock_stop(&aib, sync_port) != 0) {
		/* Sync failed. Try again in 1/2 second. */
		eacr.es = 0;
		etr_update_eacr(eacr);
		etr_set_sync_timeout();
	} else
		etr_set_tolec_timeout(now);
out_unlock:
	mutex_unlock(&etr_work_mutex);
}