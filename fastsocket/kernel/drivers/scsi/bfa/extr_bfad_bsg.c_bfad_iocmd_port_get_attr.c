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
struct TYPE_7__ {int /*<<< orphan*/  bport; } ;
struct TYPE_8__ {TYPE_1__ fabric; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa_fcs; int /*<<< orphan*/  bfa; } ;
struct TYPE_10__ {int /*<<< orphan*/  symname; } ;
struct TYPE_11__ {TYPE_4__ sym_name; } ;
struct bfa_lport_attr_s {TYPE_5__ port_cfg; int /*<<< orphan*/  authfail; int /*<<< orphan*/  loopback; int /*<<< orphan*/  port_type; scalar_t__ pid; } ;
struct TYPE_9__ {int /*<<< orphan*/  symname; } ;
struct TYPE_12__ {scalar_t__ topology; TYPE_3__ port_symname; int /*<<< orphan*/  authfail; int /*<<< orphan*/  loopback; int /*<<< orphan*/  port_type; scalar_t__ pid; } ;
struct bfa_bsg_port_attr_s {int /*<<< orphan*/  status; TYPE_6__ attr; } ;

/* Variables and functions */
 scalar_t__ BFA_PORT_TOPOLOGY_NONE ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_fcport_get_attr (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_attr (int /*<<< orphan*/ *,struct bfa_lport_attr_s*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bfad_iocmd_port_get_attr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_port_attr_s *iocmd = (struct bfa_bsg_port_attr_s *)cmd;
	struct bfa_lport_attr_s	port_attr;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcport_get_attr(&bfad->bfa, &iocmd->attr);
	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (iocmd->attr.topology != BFA_PORT_TOPOLOGY_NONE)
		iocmd->attr.pid = port_attr.pid;
	else
		iocmd->attr.pid = 0;

	iocmd->attr.port_type = port_attr.port_type;
	iocmd->attr.loopback = port_attr.loopback;
	iocmd->attr.authfail = port_attr.authfail;
	strncpy(iocmd->attr.port_symname.symname,
		port_attr.port_cfg.sym_name.symname,
		sizeof(port_attr.port_cfg.sym_name.symname));

	iocmd->status = BFA_STATUS_OK;
	return 0;
}