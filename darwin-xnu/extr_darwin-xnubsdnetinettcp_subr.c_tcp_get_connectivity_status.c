#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {scalar_t__ t_rxtshift; scalar_t__ t_rtimo_probes; TYPE_2__* t_inpcb; int /*<<< orphan*/  t_state; } ;
struct tcp_conn_status {int write_probe_failed; int conn_probe_failed; int read_probe_failed; int probe_activated; } ;
struct TYPE_4__ {TYPE_1__* inp_last_outifp; } ;
struct TYPE_3__ {int if_eflags; } ;

/* Variables and functions */
 int IFEF_PROBE_CONNECTIVITY ; 
 scalar_t__ TCPS_HAVEESTABLISHED (int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_CONNECTIVITY_PROBES_MAX ; 
 int /*<<< orphan*/  bzero (struct tcp_conn_status*,int) ; 

void
tcp_get_connectivity_status(struct tcpcb *tp,
	struct tcp_conn_status *connstatus)
{
	if (tp == NULL || connstatus == NULL)
		return;
	bzero(connstatus, sizeof(*connstatus));
	if (tp->t_rxtshift >= TCP_CONNECTIVITY_PROBES_MAX) {
		if (TCPS_HAVEESTABLISHED(tp->t_state)) {
			connstatus->write_probe_failed = 1;
		} else {
			connstatus->conn_probe_failed = 1;
		}
	}
	if (tp->t_rtimo_probes >= TCP_CONNECTIVITY_PROBES_MAX)
		connstatus->read_probe_failed = 1;
	if (tp->t_inpcb != NULL && tp->t_inpcb->inp_last_outifp != NULL &&
	    (tp->t_inpcb->inp_last_outifp->if_eflags & IFEF_PROBE_CONNECTIVITY))
		connstatus->probe_activated = 1;
}