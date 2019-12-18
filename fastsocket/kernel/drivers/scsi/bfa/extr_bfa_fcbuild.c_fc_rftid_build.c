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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fcgs_rftid_req_s {int dap; int /*<<< orphan*/ * fc4_type; } ;
struct ct_hdr_s {int dummy; } ;
typedef  enum bfa_lport_role { ____Placeholder_bfa_lport_role } bfa_lport_role ;

/* Variables and functions */
 int /*<<< orphan*/  FC_NAME_SERVER ; 
 int FC_TYPE_FCP ; 
 int /*<<< orphan*/  GS_RFT_ID ; 
 int bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fc_gs_cthdr_build (struct ct_hdr_s*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fchdr_build (struct fchs_s*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct fcgs_rftid_req_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_rftid_build(struct fchs_s *fchs, void *pyld, u32 s_id, u16 ox_id,
	       enum bfa_lport_role roles)
{
	struct ct_hdr_s *cthdr = (struct ct_hdr_s *) pyld;
	struct fcgs_rftid_req_s *rftid = (struct fcgs_rftid_req_s *)(cthdr + 1);
	u32        type_value, d_id = bfa_hton3b(FC_NAME_SERVER);
	u8         index;

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RFT_ID);

	memset(rftid, 0, sizeof(struct fcgs_rftid_req_s));

	rftid->dap = s_id;

	/* By default, FCP FC4 Type is registered */
	index = FC_TYPE_FCP >> 5;
	type_value = 1 << (FC_TYPE_FCP % 32);
	rftid->fc4_type[index] = cpu_to_be32(type_value);

	return sizeof(struct fcgs_rftid_req_s) + sizeof(struct ct_hdr_s);
}