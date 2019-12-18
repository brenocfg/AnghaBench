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
struct bfad_s {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  roles; } ;
struct bfa_fcs_lport_s {TYPE_6__* fcs; TYPE_3__ port_cfg; TYPE_2__* fabric; } ;
struct TYPE_10__ {void* lpwwn; void* ppwwn; int /*<<< orphan*/  roles; int /*<<< orphan*/  vf_id; } ;
struct TYPE_11__ {TYPE_4__ lport; } ;
struct bfa_aen_entry_s {TYPE_5__ aen_data; } ;
typedef  enum bfa_lport_aen_event { ____Placeholder_bfa_lport_aen_event } bfa_lport_aen_event ;
struct TYPE_12__ {int /*<<< orphan*/  fcs_aen_seq; } ;
struct TYPE_8__ {int /*<<< orphan*/  vf_id; TYPE_1__* fcs; } ;
struct TYPE_7__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_AEN_CAT_LPORT ; 
 struct bfa_fcs_lport_s* bfa_fcs_get_base_port (TYPE_6__*) ; 
 void* bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfad_get_aen_entry (struct bfad_s*,struct bfa_aen_entry_s*) ; 
 int /*<<< orphan*/  bfad_im_post_vendor_event (struct bfa_aen_entry_s*,struct bfad_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_aen_post(struct bfa_fcs_lport_s *port,
			enum bfa_lport_aen_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)port->fabric->fcs->bfad;
	struct bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	aen_entry->aen_data.lport.vf_id = port->fabric->vf_id;
	aen_entry->aen_data.lport.roles = port->port_cfg.roles;
	aen_entry->aen_data.lport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(port->fcs));
	aen_entry->aen_data.lport.lpwwn = bfa_fcs_lport_get_pwwn(port);

	/* Send the AEN notification */
	bfad_im_post_vendor_event(aen_entry, bfad, ++port->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_LPORT, event);
}