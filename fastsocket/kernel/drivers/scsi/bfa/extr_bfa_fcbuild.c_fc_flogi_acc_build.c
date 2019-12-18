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
typedef  void* wwn_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_6__ {void* bbcred; void* rxsz; } ;
struct TYPE_5__ {void* rxsz; } ;
struct TYPE_4__ {int /*<<< orphan*/  els_code; } ;
struct fc_logi_s {TYPE_3__ csp; void* node_name; void* port_name; TYPE_2__ class3; TYPE_1__ els_cmd; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_rsp_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fc_logi_s*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  plogi_tmpl ; 

u16
fc_flogi_acc_build(struct fchs_s *fchs, struct fc_logi_s *flogi, u32 s_id,
		   __be16 ox_id, wwn_t port_name, wwn_t node_name,
		   u16 pdu_size, u16 local_bb_credits, u8 bb_scn)
{
	u32        d_id = 0;
	u16	   bbscn_rxsz = (bb_scn << 12) | pdu_size;

	memcpy(flogi, &plogi_tmpl, sizeof(struct fc_logi_s));
	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	flogi->els_cmd.els_code = FC_ELS_ACC;
	flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->csp.rxsz  = cpu_to_be16(bbscn_rxsz);	/* bb_scn/rxsz */
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	flogi->csp.bbcred = cpu_to_be16(local_bb_credits);

	return sizeof(struct fc_logi_s);
}