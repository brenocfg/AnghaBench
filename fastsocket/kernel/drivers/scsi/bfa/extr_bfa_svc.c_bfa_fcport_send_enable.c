#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct TYPE_6__ {TYPE_2__ a32; } ;
struct TYPE_4__ {int /*<<< orphan*/  maxfrsize; } ;
struct bfi_fcport_enable_req_s {int /*<<< orphan*/  mh; TYPE_3__ stats_dma_addr; int /*<<< orphan*/  use_flash_cfg; TYPE_1__ port_cfg; scalar_t__ msgtag; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;
struct bfa_fcport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  stats_pa; int /*<<< orphan*/  use_flash_cfg; TYPE_1__ cfg; scalar_t__ msgtag; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  reqq_wait; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_PORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_FCPORT_H2I_ENABLE_REQ ; 
 int /*<<< orphan*/  BFI_MC_FCPORT ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_fcport_enable_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_fcport_send_enable(struct bfa_fcport_s *fcport)
{
	struct bfi_fcport_enable_req_s *m;

	/*
	 * Increment message tag before queue check, so that responses to old
	 * requests are discarded.
	 */
	fcport->msgtag++;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);
	if (!m) {
		bfa_reqq_wait(fcport->bfa, BFA_REQQ_PORT,
							&fcport->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_ENABLE_REQ,
			bfa_fn_lpu(fcport->bfa));
	m->nwwn = fcport->nwwn;
	m->pwwn = fcport->pwwn;
	m->port_cfg = fcport->cfg;
	m->msgtag = fcport->msgtag;
	m->port_cfg.maxfrsize = cpu_to_be16(fcport->cfg.maxfrsize);
	 m->use_flash_cfg = fcport->use_flash_cfg;
	bfa_dma_be_addr_set(m->stats_dma_addr, fcport->stats_pa);
	bfa_trc(fcport->bfa, m->stats_dma_addr.a32.addr_lo);
	bfa_trc(fcport->bfa, m->stats_dma_addr.a32.addr_hi);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, m->mh);
	return BFA_TRUE;
}