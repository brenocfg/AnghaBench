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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u8 ;
struct fc_vport {scalar_t__ dd_data; } ;
struct TYPE_4__ {TYPE_1__* im_port; struct bfad_s* bfad; } ;
struct bfad_vport_s {TYPE_2__ drv_port; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfa_fcs_vport_s {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {struct Scsi_Host* shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_ACTIVE ; 
 int /*<<< orphan*/  FC_VPORT_DISABLED ; 
 int VPCERR_BAD_WWN ; 
 struct bfa_fcs_vport_s* bfa_fcs_vport_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_vport_start (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_vport_stop (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  fc_host_port_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_vport_set_state (struct fc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  u64_to_wwn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bfad_im_vport_disable(struct fc_vport *fc_vport, bool disable)
{
	struct bfad_vport_s *vport;
	struct bfad_s *bfad;
	struct bfa_fcs_vport_s *fcs_vport;
	struct Scsi_Host *vshost;
	wwn_t   pwwn;
	unsigned long flags;

	vport = (struct bfad_vport_s *)fc_vport->dd_data;
	bfad = vport->drv_port.bfad;
	vshost = vport->drv_port.im_port->shost;
	u64_to_wwn(fc_host_port_name(vshost), (u8 *)&pwwn);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0, pwwn);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (fcs_vport == NULL)
		return VPCERR_BAD_WWN;

	if (disable) {
		bfa_fcs_vport_stop(fcs_vport);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
	} else {
		bfa_fcs_vport_start(fcs_vport);
		fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
	}

	return 0;
}