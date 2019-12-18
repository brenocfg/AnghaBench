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
struct bfad_s {int /*<<< orphan*/  bfad_flags; } ;
struct bfa_fcs_lport_s {TYPE_1__* fabric; TYPE_2__* fcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* online ) (struct bfa_fcs_lport_s*) ;int /*<<< orphan*/  (* init ) (struct bfa_fcs_lport_s*) ;} ;
struct TYPE_5__ {scalar_t__ bfad; } ;
struct TYPE_4__ {size_t fab_type; int /*<<< orphan*/  oper_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_PORT_ONLINE ; 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  BFA_LPORT_AEN_ONLINE ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 TYPE_3__* __port_action ; 
 int /*<<< orphan*/  bfa_fcs_lport_aen_post (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  stub2 (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_online_actions(struct bfa_fcs_lport_s *port)
{
	struct bfad_s *bfad = (struct bfad_s *)port->fcs->bfad;
	char	lpwwn_buf[BFA_STRING_32];

	bfa_trc(port->fcs, port->fabric->oper_type);

	__port_action[port->fabric->fab_type].init(port);
	__port_action[port->fabric->fab_type].online(port);

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
		"Logical port online: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
	bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_ONLINE);

	bfad->bfad_flags |= BFAD_PORT_ONLINE;
}