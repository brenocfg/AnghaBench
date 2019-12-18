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
struct bfad_s {int dummy; } ;
struct bfa_fcs_lport_s {TYPE_2__* fabric; scalar_t__ vport; TYPE_1__* fcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  wc; } ;
struct TYPE_3__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  BFA_LPORT_AEN_DELETE ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_fcs_lport_aen_post (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_vport_delete_comp (scalar_t__) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_deleted(struct bfa_fcs_lport_s *port)
{
	struct bfad_s *bfad = (struct bfad_s *)port->fcs->bfad;
	char    lpwwn_buf[BFA_STRING_32];

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Logical port deleted: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
	bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_DELETE);

	/* Base port will be deleted by the OS driver */
	if (port->vport)
		bfa_fcs_vport_delete_comp(port->vport);
	else
		bfa_wc_down(&port->fabric->wc);
}