#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  swp_vfid; } ;
struct TYPE_6__ {int pwwn; } ;
struct TYPE_7__ {TYPE_2__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_1__ event_arg; TYPE_4__* fcs; TYPE_3__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_8__ {int /*<<< orphan*/  port_vfid; scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_trc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  wwn2str (char*,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_isolated(struct bfa_fcs_fabric_s *fabric,
			   enum bfa_fcs_fabric_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)fabric->fcs->bfad;
	char	pwwn_ptr[BFA_STRING_32];

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);
	wwn2str(pwwn_ptr, fabric->bport.port_cfg.pwwn);

	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Port is isolated due to VF_ID mismatch. "
		"PWWN: %s Port VF_ID: %04x switch port VF_ID: %04x.",
		pwwn_ptr, fabric->fcs->port_vfid,
		fabric->event_arg.swp_vfid);
}