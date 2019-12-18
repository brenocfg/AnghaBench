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
typedef  int u8 ;
typedef  int u32 ;
struct qib_ibport {scalar_t__ mkey; int mkeyprot; int port_cap_flags; int sm_sl; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  qkey_violations; int /*<<< orphan*/  pkey_violations; int /*<<< orphan*/  mkey_violations; int /*<<< orphan*/  vl_high_limit; int /*<<< orphan*/  mkey_lease_period; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  gid_prefix; } ;
struct qib_pportdata {int link_speed_supported; int lmc; int link_speed_active; int link_speed_enabled; int ibmtu; int vls_supported; int /*<<< orphan*/  lastibcstat; int /*<<< orphan*/  link_width_active; int /*<<< orphan*/  link_width_supported; int /*<<< orphan*/  link_width_enabled; int /*<<< orphan*/  lid; struct qib_ibport ibport_data; } ;
struct qib_devdata {int (* f_iblink_state ) (int /*<<< orphan*/ ) ;int (* f_ibphys_portstate ) (int /*<<< orphan*/ ) ;int (* f_get_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;struct qib_pportdata* pport; } ;
struct ib_smp {scalar_t__ method; scalar_t__ mkey; scalar_t__ data; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_mod; } ;
struct ib_port_info {scalar_t__ mkey; int local_port_num; int linkspeed_portstate; int portphysstate_linkdown; int mkeyprot_resv_lmc; int linkspeedactive_enabled; int neighbormtu_mastersmsl; int vlcap_inittype; int vl_arb_high_cap; int vl_arb_low_cap; int operationalvl_pei_peo_fpi_fpo; int resv_resptimevalue; int localphyerrors_overrunerrors; int* link_roundtrip_latency; int /*<<< orphan*/  clientrereg_resv_subnetto; int /*<<< orphan*/  guid_cap; void* qkey_violations; void* pkey_violations; void* mkey_violations; void* inittypereply_mtucap; int /*<<< orphan*/  vl_high_limit; int /*<<< orphan*/  link_width_active; int /*<<< orphan*/  link_width_supported; int /*<<< orphan*/  link_width_enabled; void* mkey_lease_period; int /*<<< orphan*/  cap_mask; void* sm_lid; void* lid; int /*<<< orphan*/  gid_prefix; } ;
struct ib_device {int phys_port_cnt; } ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 scalar_t__ IB_MGMT_METHOD_GET ; 
 int IB_MTU_1024 ; 
 int IB_MTU_2048 ; 
 int IB_MTU_256 ; 
 void* IB_MTU_4096 ; 
 int IB_MTU_512 ; 
 int IB_PORT_LINK_LATENCY_SUP ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  QIB_GUIDS_PER_PORT ; 
 int /*<<< orphan*/  QIB_IB_CFG_LINKLATENCY ; 
 int /*<<< orphan*/  QIB_IB_CFG_OP_VLS ; 
 int /*<<< orphan*/  QIB_IB_CFG_VL_HIGH_CAP ; 
 int /*<<< orphan*/  QIB_IB_CFG_VL_LOW_CAP ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int check_mkey (struct qib_ibport*,struct ib_smp*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct qib_devdata* dd_from_ibdev (struct ib_device*) ; 
 scalar_t__ get_linkdowndefaultstate (struct qib_pportdata*) ; 
 int get_overrunthreshold (struct qib_pportdata*) ; 
 int get_phyerrthreshold (struct qib_pportdata*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 void* qib_ibmtu ; 
 int reply (struct ib_smp*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int stub3 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int stub4 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int stub5 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int stub6 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (struct ib_device*,int) ; 

__attribute__((used)) static int subn_get_portinfo(struct ib_smp *smp, struct ib_device *ibdev,
			     u8 port)
{
	struct qib_devdata *dd;
	struct qib_pportdata *ppd;
	struct qib_ibport *ibp;
	struct ib_port_info *pip = (struct ib_port_info *)smp->data;
	u8 mtu;
	int ret;
	u32 state;
	u32 port_num = be32_to_cpu(smp->attr_mod);

	if (port_num == 0)
		port_num = port;
	else {
		if (port_num > ibdev->phys_port_cnt) {
			smp->status |= IB_SMP_INVALID_FIELD;
			ret = reply(smp);
			goto bail;
		}
		if (port_num != port) {
			ibp = to_iport(ibdev, port_num);
			ret = check_mkey(ibp, smp, 0);
			if (ret) {
				ret = IB_MAD_RESULT_FAILURE;
				goto bail;
			}
		}
	}

	dd = dd_from_ibdev(ibdev);
	/* IB numbers ports from 1, hdw from 0 */
	ppd = dd->pport + (port_num - 1);
	ibp = &ppd->ibport_data;

	/* Clear all fields.  Only set the non-zero fields. */
	memset(smp->data, 0, sizeof(smp->data));

	/* Only return the mkey if the protection field allows it. */
	if (!(smp->method == IB_MGMT_METHOD_GET &&
	      ibp->mkey != smp->mkey &&
	      ibp->mkeyprot == 1))
		pip->mkey = ibp->mkey;
	pip->gid_prefix = ibp->gid_prefix;
	pip->lid = cpu_to_be16(ppd->lid);
	pip->sm_lid = cpu_to_be16(ibp->sm_lid);
	pip->cap_mask = cpu_to_be32(ibp->port_cap_flags);
	/* pip->diag_code; */
	pip->mkey_lease_period = cpu_to_be16(ibp->mkey_lease_period);
	pip->local_port_num = port;
	pip->link_width_enabled = ppd->link_width_enabled;
	pip->link_width_supported = ppd->link_width_supported;
	pip->link_width_active = ppd->link_width_active;
	state = dd->f_iblink_state(ppd->lastibcstat);
	pip->linkspeed_portstate = ppd->link_speed_supported << 4 | state;

	pip->portphysstate_linkdown =
		(dd->f_ibphys_portstate(ppd->lastibcstat) << 4) |
		(get_linkdowndefaultstate(ppd) ? 1 : 2);
	pip->mkeyprot_resv_lmc = (ibp->mkeyprot << 6) | ppd->lmc;
	pip->linkspeedactive_enabled = (ppd->link_speed_active << 4) |
		ppd->link_speed_enabled;
	switch (ppd->ibmtu) {
	default: /* something is wrong; fall through */
	case 4096:
		mtu = IB_MTU_4096;
		break;
	case 2048:
		mtu = IB_MTU_2048;
		break;
	case 1024:
		mtu = IB_MTU_1024;
		break;
	case 512:
		mtu = IB_MTU_512;
		break;
	case 256:
		mtu = IB_MTU_256;
		break;
	}
	pip->neighbormtu_mastersmsl = (mtu << 4) | ibp->sm_sl;
	pip->vlcap_inittype = ppd->vls_supported << 4;  /* InitType = 0 */
	pip->vl_high_limit = ibp->vl_high_limit;
	pip->vl_arb_high_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VL_HIGH_CAP);
	pip->vl_arb_low_cap =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_VL_LOW_CAP);
	/* InitTypeReply = 0 */
	pip->inittypereply_mtucap = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	/* HCAs ignore VLStallCount and HOQLife */
	/* pip->vlstallcnt_hoqlife; */
	pip->operationalvl_pei_peo_fpi_fpo =
		dd->f_get_ib_cfg(ppd, QIB_IB_CFG_OP_VLS) << 4;
	pip->mkey_violations = cpu_to_be16(ibp->mkey_violations);
	/* P_KeyViolations are counted by hardware. */
	pip->pkey_violations = cpu_to_be16(ibp->pkey_violations);
	pip->qkey_violations = cpu_to_be16(ibp->qkey_violations);
	/* Only the hardware GUID is supported for now */
	pip->guid_cap = QIB_GUIDS_PER_PORT;
	pip->clientrereg_resv_subnetto = ibp->subnet_timeout;
	/* 32.768 usec. response time (guessing) */
	pip->resv_resptimevalue = 3;
	pip->localphyerrors_overrunerrors =
		(get_phyerrthreshold(ppd) << 4) |
		get_overrunthreshold(ppd);
	/* pip->max_credit_hint; */
	if (ibp->port_cap_flags & IB_PORT_LINK_LATENCY_SUP) {
		u32 v;

		v = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_LINKLATENCY);
		pip->link_roundtrip_latency[0] = v >> 16;
		pip->link_roundtrip_latency[1] = v >> 8;
		pip->link_roundtrip_latency[2] = v;
	}

	ret = reply(smp);

bail:
	return ret;
}