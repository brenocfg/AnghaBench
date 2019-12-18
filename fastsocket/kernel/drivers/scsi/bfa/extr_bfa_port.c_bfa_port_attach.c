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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct bfa_trc_mod_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qe; } ;
struct bfa_port_s {int /*<<< orphan*/  stats_reset_time; struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; void* dport_enabled; void* pbc_disabled; int /*<<< orphan*/ * endis_cbfn; int /*<<< orphan*/ * stats_cbfn; void* endis_pending; void* stats_busy; struct bfa_trc_mod_s* trcmod; void* dev; } ;
struct bfa_ioc_s {int /*<<< orphan*/  notify_q; } ;

/* Variables and functions */
 void* BFA_FALSE ; 
 int /*<<< orphan*/  BFI_MC_PORT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_port_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_port_s*) ; 
 int /*<<< orphan*/  bfa_port_isr ; 
 int /*<<< orphan*/  bfa_port_notify ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_port_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_port_attach(struct bfa_port_s *port, struct bfa_ioc_s *ioc,
		 void *dev, struct bfa_trc_mod_s *trcmod)
{
	struct timeval tv;

	WARN_ON(!port);

	port->dev    = dev;
	port->ioc    = ioc;
	port->trcmod = trcmod;

	port->stats_busy = BFA_FALSE;
	port->endis_pending = BFA_FALSE;
	port->stats_cbfn = NULL;
	port->endis_cbfn = NULL;
	port->pbc_disabled = BFA_FALSE;
	port->dport_enabled = BFA_FALSE;

	bfa_ioc_mbox_regisr(port->ioc, BFI_MC_PORT, bfa_port_isr, port);
	bfa_q_qe_init(&port->ioc_notify);
	bfa_ioc_notify_init(&port->ioc_notify, bfa_port_notify, port);
	list_add_tail(&port->ioc_notify.qe, &port->ioc->notify_q);

	/*
	 * initialize time stamp for stats reset
	 */
	do_gettimeofday(&tv);
	port->stats_reset_time = tv.tv_sec;

	bfa_trc(port, 0);
}