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
typedef  void* wwn_t ;
struct bfad_s {int dummy; } ;
struct bfa_fcs_fabric_s {scalar_t__ fabric_name; int /*<<< orphan*/  bport; TYPE_1__* fcs; } ;
struct TYPE_2__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  BFA_PORT_AEN_FABRIC_NAME_CHANGE ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  bfa_fcs_fabric_aen_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fabric_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_pwwn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_fabric_set_fabric_name(struct bfa_fcs_fabric_s *fabric,
			       wwn_t fabric_name)
{
	struct bfad_s *bfad = (struct bfad_s *)fabric->fcs->bfad;
	char	pwwn_ptr[BFA_STRING_32];
	char	fwwn_ptr[BFA_STRING_32];

	bfa_trc(fabric->fcs, fabric_name);

	if (fabric->fabric_name == 0) {
		/*
		 * With BRCD switches, we don't get Fabric Name in FLOGI.
		 * Don't generate a fabric name change event in this case.
		 */
		fabric->fabric_name = fabric_name;
	} else {
		fabric->fabric_name = fabric_name;
		wwn2str(pwwn_ptr, bfa_fcs_lport_get_pwwn(&fabric->bport));
		wwn2str(fwwn_ptr,
			bfa_fcs_lport_get_fabric_name(&fabric->bport));
		BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
			"Base port WWN = %s Fabric WWN = %s\n",
			pwwn_ptr, fwwn_ptr);
		bfa_fcs_fabric_aen_post(&fabric->bport,
				BFA_PORT_AEN_FABRIC_NAME_CHANGE);
	}
}