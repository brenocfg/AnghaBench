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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int so_state; int so_flags; scalar_t__ so_error; int /*<<< orphan*/  so_rcv; TYPE_1__* so_proto; } ;
struct knote {int kn_fflags; int kn_hookid; scalar_t__ kn_data; int kn_sfflags; int /*<<< orphan*/  kn_flags; } ;
struct TYPE_2__ {int pr_flags; } ;

/* Variables and functions */
 int EVFILT_SOCK_ALL_MASK ; 
 int EVFILT_SOCK_LEVEL_TRIGGER_MASK ; 
 int /*<<< orphan*/  EV_EOF ; 
 int NOTE_ADAPTIVE_RTIMO ; 
 int NOTE_ADAPTIVE_WTIMO ; 
 int NOTE_CONNECTED ; 
 int NOTE_CONNINFO_UPDATED ; 
 int NOTE_CONNRESET ; 
 int NOTE_DISCONNECTED ; 
 int NOTE_IFDENIED ; 
 int NOTE_KEEPALIVE ; 
 int NOTE_NOSRCADDR ; 
 int NOTE_NOTIFY_ACK ; 
 int NOTE_READCLOSED ; 
 int NOTE_RESUME ; 
 int NOTE_SUSPEND ; 
 int NOTE_TIMEOUT ; 
 int NOTE_WRITECLOSED ; 
 int PR_EVCONNINFO ; 
 int SOF_SUSPENDED ; 
 long SO_FILT_HINT_ADAPTIVE_RTIMO ; 
 long SO_FILT_HINT_ADAPTIVE_WTIMO ; 
 long SO_FILT_HINT_CONNECTED ; 
 long SO_FILT_HINT_CONNINFO_UPDATED ; 
 long SO_FILT_HINT_CONNRESET ; 
 long SO_FILT_HINT_DISCONNECTED ; 
 long SO_FILT_HINT_IFDENIED ; 
 long SO_FILT_HINT_KEEPALIVE ; 
 long SO_FILT_HINT_NOSRCADDR ; 
 long SO_FILT_HINT_NOTIFY_ACK ; 
 long SO_FILT_HINT_RESUME ; 
 long SO_FILT_HINT_SUSPEND ; 
 long SO_FILT_HINT_TIMEOUT ; 
 int SS_CANTRCVMORE ; 
 int SS_CANTSENDMORE ; 
 int SS_ISCONNECTED ; 
 int SS_ISDISCONNECTED ; 
 scalar_t__ cfil_sock_data_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_sockev_state (struct socket*,int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_notify_ack_active (struct socket*) ; 

__attribute__((used)) static int
filt_sockev_common(struct knote *kn, struct socket *so, long ev_hint)
{
	int ret = 0;
	uint32_t level_trigger = 0;

	if (ev_hint & SO_FILT_HINT_CONNRESET) {
		kn->kn_fflags |= NOTE_CONNRESET;
	}
	if (ev_hint & SO_FILT_HINT_TIMEOUT) {
		kn->kn_fflags |= NOTE_TIMEOUT;
	}
	if (ev_hint & SO_FILT_HINT_NOSRCADDR) {
		kn->kn_fflags |= NOTE_NOSRCADDR;
	}
	if (ev_hint & SO_FILT_HINT_IFDENIED) {
		kn->kn_fflags |= NOTE_IFDENIED;
	}
	if (ev_hint & SO_FILT_HINT_KEEPALIVE) {
		kn->kn_fflags |= NOTE_KEEPALIVE;
	}
	if (ev_hint & SO_FILT_HINT_ADAPTIVE_WTIMO) {
		kn->kn_fflags |= NOTE_ADAPTIVE_WTIMO;
	}
	if (ev_hint & SO_FILT_HINT_ADAPTIVE_RTIMO) {
		kn->kn_fflags |= NOTE_ADAPTIVE_RTIMO;
	}
	if ((ev_hint & SO_FILT_HINT_CONNECTED) ||
	    (so->so_state & SS_ISCONNECTED)) {
		kn->kn_fflags |= NOTE_CONNECTED;
		level_trigger |= NOTE_CONNECTED;
	}
	if ((ev_hint & SO_FILT_HINT_DISCONNECTED) ||
	    (so->so_state & SS_ISDISCONNECTED)) {
		kn->kn_fflags |= NOTE_DISCONNECTED;
		level_trigger |= NOTE_DISCONNECTED;
	}
	if (ev_hint & SO_FILT_HINT_CONNINFO_UPDATED) {
		if (so->so_proto != NULL &&
		    (so->so_proto->pr_flags & PR_EVCONNINFO))
			kn->kn_fflags |= NOTE_CONNINFO_UPDATED;
	}

	if ((ev_hint & SO_FILT_HINT_NOTIFY_ACK) ||
	    tcp_notify_ack_active(so)) {
		kn->kn_fflags |= NOTE_NOTIFY_ACK;
	}

	if ((so->so_state & SS_CANTRCVMORE)
#if CONTENT_FILTER
	    && cfil_sock_data_pending(&so->so_rcv) == 0
#endif /* CONTENT_FILTER */
	    ) {
		kn->kn_fflags |= NOTE_READCLOSED;
		level_trigger |= NOTE_READCLOSED;
	}

	if (so->so_state & SS_CANTSENDMORE) {
		kn->kn_fflags |= NOTE_WRITECLOSED;
		level_trigger |= NOTE_WRITECLOSED;
	}

	if ((ev_hint & SO_FILT_HINT_SUSPEND) ||
	    (so->so_flags & SOF_SUSPENDED)) {
		kn->kn_fflags &= ~(NOTE_SUSPEND | NOTE_RESUME);

		/* If resume event was delivered before, reset it */
		kn->kn_hookid &= ~NOTE_RESUME;

		kn->kn_fflags |= NOTE_SUSPEND;
		level_trigger |= NOTE_SUSPEND;
	}

	if ((ev_hint & SO_FILT_HINT_RESUME) ||
	    (so->so_flags & SOF_SUSPENDED) == 0) {
		kn->kn_fflags &= ~(NOTE_SUSPEND | NOTE_RESUME);

		/* If suspend event was delivered before, reset it */
		kn->kn_hookid &= ~NOTE_SUSPEND;

		kn->kn_fflags |= NOTE_RESUME;
		level_trigger |= NOTE_RESUME;
	}

	if (so->so_error != 0) {
		ret = 1;
		kn->kn_data = so->so_error;
		kn->kn_flags |= EV_EOF;
	} else {
		get_sockev_state(so, (u_int32_t *)&(kn->kn_data));
	}

	/* Reset any events that are not requested on this knote */
	kn->kn_fflags &= (kn->kn_sfflags & EVFILT_SOCK_ALL_MASK);
	level_trigger &= (kn->kn_sfflags & EVFILT_SOCK_ALL_MASK);

	/* Find the level triggerred events that are already delivered */
	level_trigger &= kn->kn_hookid;
	level_trigger &= EVFILT_SOCK_LEVEL_TRIGGER_MASK;

	/* Do not deliver level triggerred events more than once */
	if ((kn->kn_fflags & ~level_trigger) != 0)
		ret = 1;

	return (ret);
}