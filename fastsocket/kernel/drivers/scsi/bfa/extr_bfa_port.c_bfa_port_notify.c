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
struct bfa_port_s {int /*<<< orphan*/  dport_enabled; void* endis_pending; int /*<<< orphan*/  (* endis_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  endis_cbarg; void* stats_busy; int /*<<< orphan*/  (* stats_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  stats_cbarg; } ;
typedef  enum bfa_ioc_event_e { ____Placeholder_bfa_ioc_event_e } bfa_ioc_event_e ;

/* Variables and functions */
 void* BFA_FALSE ; 
#define  BFA_IOC_E_DISABLED 129 
#define  BFA_IOC_E_FAILED 128 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  bfa_port_set_dportenabled (struct bfa_port_s*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_port_notify(void *arg, enum bfa_ioc_event_e event)
{
	struct bfa_port_s *port = (struct bfa_port_s *) arg;

	switch (event) {
	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		/* Fail any pending get_stats/clear_stats requests */
		if (port->stats_busy) {
			if (port->stats_cbfn)
				port->stats_cbfn(port->stats_cbarg,
						BFA_STATUS_FAILED);
			port->stats_cbfn = NULL;
			port->stats_busy = BFA_FALSE;
		}

		/* Clear any enable/disable is pending */
		if (port->endis_pending) {
			if (port->endis_cbfn)
				port->endis_cbfn(port->endis_cbarg,
						BFA_STATUS_FAILED);
			port->endis_cbfn = NULL;
			port->endis_pending = BFA_FALSE;
		}

		/* clear D-port mode */
		if (port->dport_enabled)
			bfa_port_set_dportenabled(port, BFA_FALSE);
		break;
	default:
		break;
	}
}