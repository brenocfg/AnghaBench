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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  clean_address_bit; } ;
struct serv_parm {TYPE_1__ cmn; int /*<<< orphan*/  nodeName; int /*<<< orphan*/  portName; } ;
struct lpfc_vport {scalar_t__ fc_prevDID; scalar_t__ fc_myDID; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  fabric_nodename; int /*<<< orphan*/  fabric_portname; } ;
struct lpfc_name {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_DISC_DELAYED ; 
 scalar_t__ lpfc_delay_discovery ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
lpfc_check_clean_addr_bit(struct lpfc_vport *vport,
		struct serv_parm *sp)
{
	uint8_t fabric_param_changed = 0;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	if ((vport->fc_prevDID != vport->fc_myDID) ||
		memcmp(&vport->fabric_portname, &sp->portName,
			sizeof(struct lpfc_name)) ||
		memcmp(&vport->fabric_nodename, &sp->nodeName,
			sizeof(struct lpfc_name)))
		fabric_param_changed = 1;

	/*
	 * Word 1 Bit 31 in common service parameter is overloaded.
	 * Word 1 Bit 31 in FLOGI request is multiple NPort request
	 * Word 1 Bit 31 in FLOGI response is clean address bit
	 *
	 * If fabric parameter is changed and clean address bit is
	 * cleared delay nport discovery if
	 * - vport->fc_prevDID != 0 (not initial discovery) OR
	 * - lpfc_delay_discovery module parameter is set.
	 */
	if (fabric_param_changed && !sp->cmn.clean_address_bit &&
	    (vport->fc_prevDID || lpfc_delay_discovery)) {
		spin_lock_irq(shost->host_lock);
		vport->fc_flag |= FC_DISC_DELAYED;
		spin_unlock_irq(shost->host_lock);
	}

	return fabric_param_changed;
}