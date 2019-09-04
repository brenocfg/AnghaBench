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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct ifnet_poll_params {scalar_t__ packets_lowat; scalar_t__ packets_hiwat; scalar_t__ bytes_lowat; scalar_t__ bytes_hiwat; scalar_t__ interval_time; scalar_t__ packets_limit; } ;
struct ifnet {int if_eflags; scalar_t__ if_poll_update; struct dlil_threading_info* if_inp; } ;
struct dlil_threading_info {int rxpoll_wlowat; int rxpoll_plowat; int rxpoll_blowat; int rxpoll_whiwat; int rxpoll_phiwat; int rxpoll_bhiwat; int rxpoll_plim; int rxpoll_ival; int /*<<< orphan*/  input_lck; int /*<<< orphan*/  sample_holdtime; int /*<<< orphan*/  mode_holdtime; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {scalar_t__ speed; scalar_t__ plowat; scalar_t__ phiwat; scalar_t__ blowat; scalar_t__ bhiwat; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_RXPOLL ; 
 scalar_t__ IF_RXPOLL_INTERVALTIME_MIN ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ dlil_verbose ; 
 char* if_name (struct ifnet*) ; 
 scalar_t__ if_rxpoll_interval_time ; 
 scalar_t__ if_rxpoll_max ; 
 scalar_t__ if_rxpoll_mode_holdtime ; 
 scalar_t__ if_rxpoll_sample_holdtime ; 
 int if_rxpoll_whiwat ; 
 int if_rxpoll_wlowat ; 
 scalar_t__ ifnet_input_linkrate (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_nsectimer (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,scalar_t__,int,int,int,int,int,int,int,int) ; 
 TYPE_1__* rxpoll_tbl ; 

errno_t
dlil_rxpoll_set_params(struct ifnet *ifp, struct ifnet_poll_params *p,
    boolean_t locked)
{
	struct dlil_threading_info *inp;
	u_int64_t sample_holdtime, inbw;

	VERIFY(ifp != NULL);
	if (!(ifp->if_eflags & IFEF_RXPOLL) || (inp = ifp->if_inp) == NULL)
		return (ENXIO);

	if (p != NULL) {
		if ((p->packets_lowat == 0 && p->packets_hiwat != 0) ||
		    (p->packets_lowat != 0 && p->packets_hiwat == 0))
			return (EINVAL);
		if (p->packets_lowat != 0 &&	/* hiwat must be non-zero */
		    p->packets_lowat >= p->packets_hiwat)
			return (EINVAL);
		if ((p->bytes_lowat == 0 && p->bytes_hiwat != 0) ||
		    (p->bytes_lowat != 0 && p->bytes_hiwat == 0))
			return (EINVAL);
		if (p->bytes_lowat != 0 &&	/* hiwat must be non-zero */
		    p->bytes_lowat >= p->bytes_hiwat)
			return (EINVAL);
		if (p->interval_time != 0 &&
		    p->interval_time < IF_RXPOLL_INTERVALTIME_MIN)
			p->interval_time = IF_RXPOLL_INTERVALTIME_MIN;
	}

	if (!locked)
		lck_mtx_lock(&inp->input_lck);

	LCK_MTX_ASSERT(&inp->input_lck, LCK_MTX_ASSERT_OWNED);

	/*
	 * Normally, we'd reset the parameters to the auto-tuned values
	 * if the the input thread detects a change in link rate.  If the
	 * driver provides its own parameters right after a link rate
	 * changes, but before the input thread gets to run, we want to
	 * make sure to keep the driver's values.  Clearing if_poll_update
	 * will achieve that.
	 */
	if (p != NULL && !locked && ifp->if_poll_update != 0)
		ifp->if_poll_update = 0;

	if ((inbw = ifnet_input_linkrate(ifp)) == 0 && p == NULL) {
		sample_holdtime = 0;	/* polling is disabled */
		inp->rxpoll_wlowat = inp->rxpoll_plowat =
		    inp->rxpoll_blowat = 0;
		inp->rxpoll_whiwat = inp->rxpoll_phiwat =
		    inp->rxpoll_bhiwat = (u_int32_t)-1;
		inp->rxpoll_plim = 0;
		inp->rxpoll_ival = IF_RXPOLL_INTERVALTIME_MIN;
	} else {
		u_int32_t plowat, phiwat, blowat, bhiwat, plim;
		u_int64_t ival;
		unsigned int n, i;

		for (n = 0, i = 0; rxpoll_tbl[i].speed != 0; i++) {
			if (inbw < rxpoll_tbl[i].speed)
				break;
			n = i;
		}
		/* auto-tune if caller didn't specify a value */
		plowat = ((p == NULL || p->packets_lowat == 0) ?
		    rxpoll_tbl[n].plowat : p->packets_lowat);
		phiwat = ((p == NULL || p->packets_hiwat == 0) ?
		    rxpoll_tbl[n].phiwat : p->packets_hiwat);
		blowat = ((p == NULL || p->bytes_lowat == 0) ?
		    rxpoll_tbl[n].blowat : p->bytes_lowat);
		bhiwat = ((p == NULL || p->bytes_hiwat == 0) ?
		    rxpoll_tbl[n].bhiwat : p->bytes_hiwat);
		plim = ((p == NULL || p->packets_limit == 0) ?
		    if_rxpoll_max : p->packets_limit);
		ival = ((p == NULL || p->interval_time == 0) ?
		    if_rxpoll_interval_time : p->interval_time);

		VERIFY(plowat != 0 && phiwat != 0);
		VERIFY(blowat != 0 && bhiwat != 0);
		VERIFY(ival >= IF_RXPOLL_INTERVALTIME_MIN);

		sample_holdtime = if_rxpoll_sample_holdtime;
		inp->rxpoll_wlowat = if_rxpoll_wlowat;
		inp->rxpoll_whiwat = if_rxpoll_whiwat;
		inp->rxpoll_plowat = plowat;
		inp->rxpoll_phiwat = phiwat;
		inp->rxpoll_blowat = blowat;
		inp->rxpoll_bhiwat = bhiwat;
		inp->rxpoll_plim = plim;
		inp->rxpoll_ival = ival;
	}

	net_nsectimer(&if_rxpoll_mode_holdtime, &inp->mode_holdtime);
	net_nsectimer(&sample_holdtime, &inp->sample_holdtime);

	if (dlil_verbose) {
		printf("%s: speed %llu bps, sample per %llu nsec, "
		    "poll interval %llu nsec, pkts per poll %u, "
		    "pkt limits [%u/%u], wreq limits [%u/%u], "
		    "bytes limits [%u/%u]\n", if_name(ifp),
		    inbw, sample_holdtime, inp->rxpoll_ival, inp->rxpoll_plim,
		    inp->rxpoll_plowat, inp->rxpoll_phiwat, inp->rxpoll_wlowat,
		    inp->rxpoll_whiwat, inp->rxpoll_blowat, inp->rxpoll_bhiwat);
	}

	if (!locked)
		lck_mtx_unlock(&inp->input_lck);

	return (0);
}