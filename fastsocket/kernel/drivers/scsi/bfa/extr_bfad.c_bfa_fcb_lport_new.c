#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfad_port_s {int roles; struct bfa_fcs_lport_s* fcs_port; int /*<<< orphan*/  pvb_type; } ;
struct bfad_vport_s {struct bfad_port_s drv_port; } ;
struct bfad_vf_s {struct bfad_port_s base_port; } ;
struct bfad_s {struct bfad_port_s pport; } ;
struct bfa_fcs_lport_s {int dummy; } ;
typedef  enum bfa_lport_role { ____Placeholder_bfa_lport_role } bfa_lport_role ;
typedef  scalar_t__ bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_PORT_PHYS_BASE ; 
 int /*<<< orphan*/  BFAD_PORT_PHYS_VPORT ; 
 int /*<<< orphan*/  BFAD_PORT_VF_BASE ; 
 int /*<<< orphan*/  BFAD_PORT_VF_VPORT ; 
 int BFA_LPORT_ROLE_FCP_IM ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfad_im_port_delete (struct bfad_s*,struct bfad_port_s*) ; 
 scalar_t__ bfad_im_port_new (struct bfad_s*,struct bfad_port_s*) ; 

struct bfad_port_s *
bfa_fcb_lport_new(struct bfad_s *bfad, struct bfa_fcs_lport_s *port,
		 enum bfa_lport_role roles, struct bfad_vf_s *vf_drv,
		 struct bfad_vport_s *vp_drv)
{
	bfa_status_t	rc;
	struct bfad_port_s    *port_drv;

	if (!vp_drv && !vf_drv) {
		port_drv = &bfad->pport;
		port_drv->pvb_type = BFAD_PORT_PHYS_BASE;
	} else if (!vp_drv && vf_drv) {
		port_drv = &vf_drv->base_port;
		port_drv->pvb_type = BFAD_PORT_VF_BASE;
	} else if (vp_drv && !vf_drv) {
		port_drv = &vp_drv->drv_port;
		port_drv->pvb_type = BFAD_PORT_PHYS_VPORT;
	} else {
		port_drv = &vp_drv->drv_port;
		port_drv->pvb_type = BFAD_PORT_VF_VPORT;
	}

	port_drv->fcs_port = port;
	port_drv->roles = roles;

	if (roles & BFA_LPORT_ROLE_FCP_IM) {
		rc = bfad_im_port_new(bfad, port_drv);
		if (rc != BFA_STATUS_OK) {
			bfad_im_port_delete(bfad, port_drv);
			port_drv = NULL;
		}
	}

	return port_drv;
}