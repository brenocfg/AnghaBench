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
struct TYPE_2__ {scalar_t__ sb_cc; scalar_t__ sb_ctl; scalar_t__ sb_lowat; scalar_t__ sb_hiwat; } ;
struct socket {int so_options; scalar_t__ so_qlen; scalar_t__ so_oobmark; int so_state; int so_error; TYPE_1__ so_rcv; int /*<<< orphan*/  so_comp; } ;
struct knote {scalar_t__ kn_data; int kn_sfflags; int kn_fflags; scalar_t__ kn_sdata; int /*<<< orphan*/  kn_flags; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int NOTE_LOWAT ; 
 int NOTE_OOB ; 
 int SO_ACCEPTCONN ; 
 int SS_CANTRCVMORE ; 
 int SS_RCVATMARK ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ cfil_sock_data_pending (TYPE_1__*) ; 

__attribute__((used)) static int
filt_soread_common(struct knote *kn, struct socket *so)
{
	if (so->so_options & SO_ACCEPTCONN) {
		int is_not_empty;

		/*
		 * Radar 6615193 handle the listen case dynamically
		 * for kqueue read filter. This allows to call listen()
		 * after registering the kqueue EVFILT_READ.
		 */

		kn->kn_data = so->so_qlen;
		is_not_empty = ! TAILQ_EMPTY(&so->so_comp);

		return (is_not_empty);
	}

	/* socket isn't a listener */
	/*
	 * NOTE_LOWAT specifies new low water mark in data, i.e.
	 * the bytes of protocol data. We therefore exclude any
	 * control bytes.
	 */
	kn->kn_data = so->so_rcv.sb_cc - so->so_rcv.sb_ctl;

	if (kn->kn_sfflags & NOTE_OOB) {
		if (so->so_oobmark || (so->so_state & SS_RCVATMARK)) {
			kn->kn_fflags |= NOTE_OOB;
			kn->kn_data -= so->so_oobmark;
			return (1);
		}
	}

	if ((so->so_state & SS_CANTRCVMORE)
#if CONTENT_FILTER
	    && cfil_sock_data_pending(&so->so_rcv) == 0
#endif /* CONTENT_FILTER */
	   ) {
		kn->kn_flags |= EV_EOF;
		kn->kn_fflags = so->so_error;
		return (1);
	}

	if (so->so_error) {	/* temporary udp error */
		return (1);
	}

	int64_t	lowwat = so->so_rcv.sb_lowat;
	/*
	 * Ensure that when NOTE_LOWAT is used, the derived
	 * low water mark is bounded by socket's rcv buf's
	 * high and low water mark values.
	 */
	if (kn->kn_sfflags & NOTE_LOWAT) {
		if (kn->kn_sdata > so->so_rcv.sb_hiwat)
			lowwat = so->so_rcv.sb_hiwat;
		else if (kn->kn_sdata > lowwat)
			lowwat = kn->kn_sdata;
	}

	/*
	 * The order below is important. Since NOTE_LOWAT
	 * overrides sb_lowat, check for NOTE_LOWAT case
	 * first.
	 */
	if (kn->kn_sfflags & NOTE_LOWAT)
		return (kn->kn_data >= lowwat);

	return (so->so_rcv.sb_cc >= lowwat);
}