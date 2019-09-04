#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
struct knote {int kn_status; scalar_t__* kn_ext; scalar_t__ kn_hook; } ;
typedef  scalar_t__ mach_msg_type_name_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_3__ {scalar_t__ ip_specialreply; } ;

/* Variables and functions */
 int KN_LOCKED ; 
 int KN_SUPPRESSED ; 
 scalar_t__ MACH_MSG_TYPE_PORT_RECEIVE ; 
 scalar_t__ MACH_MSG_TYPE_PORT_SEND_ONCE ; 
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_KNOTE ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct turnstile* filt_machport_kqueue_turnstile (struct knote*) ; 
 struct turnstile* turnstile_alloc () ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 struct turnstile* turnstile_prepare (uintptr_t,struct turnstile**,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,struct turnstile*,int) ; 

void
filt_machport_turnstile_prepare_lazily(
		struct knote *kn,
		mach_msg_type_name_t msgt_name,
		ipc_port_t port)
{
	/* This is called from within filt_machportprocess */
	assert((kn->kn_status & KN_SUPPRESSED) && (kn->kn_status & KN_LOCKED));

	struct turnstile *ts = filt_machport_kqueue_turnstile(kn);
	if (ts == TURNSTILE_NULL || kn->kn_ext[3] == 0 || kn->kn_hook)
		return;

	if ((msgt_name == MACH_MSG_TYPE_PORT_SEND_ONCE && port->ip_specialreply) ||
			(msgt_name == MACH_MSG_TYPE_PORT_RECEIVE)) {
		struct turnstile *kn_ts = turnstile_alloc();
		kn_ts = turnstile_prepare((uintptr_t)kn,
				(struct turnstile **)&kn->kn_hook, kn_ts, TURNSTILE_KNOTE);
		turnstile_update_inheritor(kn_ts, ts,
				TURNSTILE_IMMEDIATE_UPDATE | TURNSTILE_INHERITOR_TURNSTILE);
		turnstile_cleanup();
	}
}