#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct ct_hdr_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wwn; } ;
typedef  TYPE_1__ fcgs_gmal_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_GSSUBTYPE_CFGSERVER ; 
 int /*<<< orphan*/  FC_MGMT_SERVER ; 
 int /*<<< orphan*/  GS_FC_GMAL_CMD ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fchdr_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_ms_cthdr_build (struct ct_hdr_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

u16
fc_gmal_req_build(struct fchs_s *fchs, void *pyld, u32 s_id, wwn_t wwn)
{
	struct ct_hdr_s *cthdr = (struct ct_hdr_s *) pyld;
	fcgs_gmal_req_t *gmal = (fcgs_gmal_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_MGMT_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_ms_cthdr_build(cthdr, s_id, GS_FC_GMAL_CMD,
			CT_GSSUBTYPE_CFGSERVER);

	memset(gmal, 0, sizeof(fcgs_gmal_req_t));
	gmal->wwn = wwn;

	return sizeof(struct ct_hdr_s) + sizeof(fcgs_gmal_req_t);
}