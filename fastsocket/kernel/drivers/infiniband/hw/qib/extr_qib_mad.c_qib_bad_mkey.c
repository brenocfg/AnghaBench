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
typedef  int /*<<< orphan*/  u8 ;
struct qib_ibport {int dummy; } ;
struct ib_smp {scalar_t__ mgmt_class; int /*<<< orphan*/  return_path; int /*<<< orphan*/  hop_cnt; int /*<<< orphan*/  dr_slid; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; } ;
struct TYPE_4__ {int /*<<< orphan*/  dr_rtn_path; int /*<<< orphan*/  dr_trunc_hop; int /*<<< orphan*/  dr_slid; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; int /*<<< orphan*/  lid; } ;
struct TYPE_6__ {TYPE_1__ ntc_256; } ;
struct ib_mad_notice_attr {TYPE_3__ details; int /*<<< orphan*/  issuer_lid; scalar_t__ toggle_count; int /*<<< orphan*/  trap_num; int /*<<< orphan*/  prod_type_lsb; scalar_t__ prod_type_msb; int /*<<< orphan*/  generic_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 int /*<<< orphan*/  IB_NOTICE_PROD_CA ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_BAD_MKEY ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_DR_NOTICE ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_DR_TRUNC ; 
 int /*<<< orphan*/  IB_NOTICE_TYPE_SECURITY ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_send_trap (struct qib_ibport*,struct ib_mad_notice_attr*,int) ; 

__attribute__((used)) static void qib_bad_mkey(struct qib_ibport *ibp, struct ib_smp *smp)
{
	struct ib_mad_notice_attr data;

	/* Send violation trap */
	data.generic_type = IB_NOTICE_TYPE_SECURITY;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_BAD_MKEY;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	memset(&data.details, 0, sizeof data.details);
	data.details.ntc_256.lid = data.issuer_lid;
	data.details.ntc_256.method = smp->method;
	data.details.ntc_256.attr_id = smp->attr_id;
	data.details.ntc_256.attr_mod = smp->attr_mod;
	data.details.ntc_256.mkey = smp->mkey;
	if (smp->mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
		u8 hop_cnt;

		data.details.ntc_256.dr_slid = smp->dr_slid;
		data.details.ntc_256.dr_trunc_hop = IB_NOTICE_TRAP_DR_NOTICE;
		hop_cnt = smp->hop_cnt;
		if (hop_cnt > ARRAY_SIZE(data.details.ntc_256.dr_rtn_path)) {
			data.details.ntc_256.dr_trunc_hop |=
				IB_NOTICE_TRAP_DR_TRUNC;
			hop_cnt = ARRAY_SIZE(data.details.ntc_256.dr_rtn_path);
		}
		data.details.ntc_256.dr_trunc_hop |= hop_cnt;
		memcpy(data.details.ntc_256.dr_rtn_path, smp->return_path,
		       hop_cnt);
	}

	qib_send_trap(ibp, &data, sizeof data);
}