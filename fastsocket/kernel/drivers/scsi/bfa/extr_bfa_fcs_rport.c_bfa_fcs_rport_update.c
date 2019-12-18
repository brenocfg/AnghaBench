#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bbcred; int /*<<< orphan*/  rxsz; int /*<<< orphan*/  cisc; } ;
struct TYPE_8__ {int /*<<< orphan*/  rxsz; scalar_t__ class_valid; } ;
struct TYPE_7__ {scalar_t__ class_valid; } ;
struct fc_logi_s {TYPE_3__ csp; TYPE_2__ class3; TYPE_1__ class2; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; } ;
struct bfa_fcs_rport_s {scalar_t__ maxfrsize; int /*<<< orphan*/  cisc; int /*<<< orphan*/  fc_cos; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; TYPE_4__* port; } ;
struct TYPE_10__ {TYPE_6__* fabric; TYPE_5__* fcs; } ;
typedef  TYPE_4__ bfa_fcs_lport_t ;
struct TYPE_12__ {scalar_t__ bb_credit; } ;
struct TYPE_11__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CLASS_2 ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_set_tx_bbcredit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_is_switched (TYPE_6__*) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static void
bfa_fcs_rport_update(struct bfa_fcs_rport_s *rport, struct fc_logi_s *plogi)
{
	bfa_fcs_lport_t *port = rport->port;

	/*
	 * - port name
	 * - node name
	 */
	rport->pwwn = plogi->port_name;
	rport->nwwn = plogi->node_name;

	/*
	 * - class of service
	 */
	rport->fc_cos = 0;
	if (plogi->class3.class_valid)
		rport->fc_cos = FC_CLASS_3;

	if (plogi->class2.class_valid)
		rport->fc_cos |= FC_CLASS_2;

	/*
	 * - CISC
	 * - MAX receive frame size
	 */
	rport->cisc = plogi->csp.cisc;
	if (be16_to_cpu(plogi->class3.rxsz) < be16_to_cpu(plogi->csp.rxsz))
		rport->maxfrsize = be16_to_cpu(plogi->class3.rxsz);
	else
		rport->maxfrsize = be16_to_cpu(plogi->csp.rxsz);

	bfa_trc(port->fcs, be16_to_cpu(plogi->csp.bbcred));
	bfa_trc(port->fcs, port->fabric->bb_credit);
	/*
	 * Direct Attach P2P mode :
	 * This is to handle a bug (233476) in IBM targets in Direct Attach
	 *  Mode. Basically, in FLOGI Accept the target would have
	 * erroneously set the BB Credit to the value used in the FLOGI
	 * sent by the HBA. It uses the correct value (its own BB credit)
	 * in PLOGI.
	 */
	if ((!bfa_fcs_fabric_is_switched(port->fabric))	 &&
		(be16_to_cpu(plogi->csp.bbcred) < port->fabric->bb_credit)) {

		bfa_trc(port->fcs, be16_to_cpu(plogi->csp.bbcred));
		bfa_trc(port->fcs, port->fabric->bb_credit);

		port->fabric->bb_credit = be16_to_cpu(plogi->csp.bbcred);
		bfa_fcport_set_tx_bbcredit(port->fcs->bfa,
					  port->fabric->bb_credit);
	}

}