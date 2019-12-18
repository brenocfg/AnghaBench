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
struct ipath_ibdev {scalar_t__ mkey; int mkeyprot; int sm_lid; int port_cap_flags; int mkey_lease_period; size_t sm_sl; int mkey_violations; int z_pkey_violations; int qkey_violations; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  vl_high_limit; int /*<<< orphan*/  gid_prefix; struct ipath_devdata* dd; } ;
struct ipath_devdata {int ipath_lid; int ipath_link_speed_supported; size_t ipath_lastibcstat; size_t ibcs_lts_mask; int ipath_lmc; int ipath_link_speed_active; int ipath_link_speed_enabled; int ipath_ibmtu; int (* ipath_f_get_ib_cfg ) (struct ipath_devdata*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ipath_link_width_active; int /*<<< orphan*/  ipath_link_width_supported; int /*<<< orphan*/  ipath_link_width_enabled; } ;
struct ib_smp {scalar_t__ method; scalar_t__ mkey; scalar_t__ data; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_mod; } ;
struct ib_port_info {scalar_t__ mkey; size_t local_port_num; int linkspeed_portstate; int portphysstate_linkdown; int mkeyprot_resv_lmc; int linkspeedactive_enabled; size_t neighbormtu_mastersmsl; int vlcap_inittype; int operationalvl_pei_peo_fpi_fpo; int guid_cap; int resv_resptimevalue; int localphyerrors_overrunerrors; int* link_roundtrip_latency; int /*<<< orphan*/  clientrereg_resv_subnetto; void* qkey_violations; void* pkey_violations; void* mkey_violations; void* inittypereply_mtucap; int /*<<< orphan*/  vl_high_limit; int /*<<< orphan*/  link_width_active; int /*<<< orphan*/  link_width_supported; int /*<<< orphan*/  link_width_enabled; void* mkey_lease_period; int /*<<< orphan*/  cap_mask; void* sm_lid; void* lid; int /*<<< orphan*/  gid_prefix; } ;
struct ib_device {scalar_t__ phys_port_cnt; } ;

/* Variables and functions */
 void* IB_LID_PERMISSIVE ; 
 scalar_t__ IB_MGMT_METHOD_SET ; 
 size_t IB_MTU_1024 ; 
 void* IB_MTU_2048 ; 
 size_t IB_MTU_256 ; 
 void* IB_MTU_4096 ; 
 size_t IB_MTU_512 ; 
 int IB_PORT_LINK_LATENCY_SUP ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  IPATH_IB_CFG_LINKLATENCY ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ get_linkdowndefaultstate (struct ipath_devdata*) ; 
 int get_overrunthreshold (struct ipath_devdata*) ; 
 int get_phyerrthreshold (struct ipath_devdata*) ; 
 int* ipath_cvt_physportstate ; 
 int ipath_get_cr_errpkey (struct ipath_devdata*) ; 
 int ipath_ib_linkstate (struct ipath_devdata*,size_t) ; 
 scalar_t__ ipath_mtu4096 ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 
 int stub1 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int recv_subn_get_portinfo(struct ib_smp *smp,
				  struct ib_device *ibdev, u8 port)
{
	struct ipath_ibdev *dev;
	struct ipath_devdata *dd;
	struct ib_port_info *pip = (struct ib_port_info *)smp->data;
	u16 lid;
	u8 ibcstat;
	u8 mtu;
	int ret;

	if (be32_to_cpu(smp->attr_mod) > ibdev->phys_port_cnt) {
		smp->status |= IB_SMP_INVALID_FIELD;
		ret = reply(smp);
		goto bail;
	}

	dev = to_idev(ibdev);
	dd = dev->dd;

	/* Clear all fields.  Only set the non-zero fields. */
	memset(smp->data, 0, sizeof(smp->data));

	/* Only return the mkey if the protection field allows it. */
	if (smp->method == IB_MGMT_METHOD_SET || dev->mkey == smp->mkey ||
	    dev->mkeyprot == 0)
		pip->mkey = dev->mkey;
	pip->gid_prefix = dev->gid_prefix;
	lid = dd->ipath_lid;
	pip->lid = lid ? cpu_to_be16(lid) : IB_LID_PERMISSIVE;
	pip->sm_lid = cpu_to_be16(dev->sm_lid);
	pip->cap_mask = cpu_to_be32(dev->port_cap_flags);
	/* pip->diag_code; */
	pip->mkey_lease_period = cpu_to_be16(dev->mkey_lease_period);
	pip->local_port_num = port;
	pip->link_width_enabled = dd->ipath_link_width_enabled;
	pip->link_width_supported = dd->ipath_link_width_supported;
	pip->link_width_active = dd->ipath_link_width_active;
	pip->linkspeed_portstate = dd->ipath_link_speed_supported << 4;
	ibcstat = dd->ipath_lastibcstat;
	/* map LinkState to IB portinfo values.  */
	pip->linkspeed_portstate |= ipath_ib_linkstate(dd, ibcstat) + 1;

	pip->portphysstate_linkdown =
		(ipath_cvt_physportstate[ibcstat & dd->ibcs_lts_mask] << 4) |
		(get_linkdowndefaultstate(dd) ? 1 : 2);
	pip->mkeyprot_resv_lmc = (dev->mkeyprot << 6) | dd->ipath_lmc;
	pip->linkspeedactive_enabled = (dd->ipath_link_speed_active << 4) |
		dd->ipath_link_speed_enabled;
	switch (dd->ipath_ibmtu) {
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
	default:		/* oops, something is wrong */
		mtu = IB_MTU_2048;
		break;
	}
	pip->neighbormtu_mastersmsl = (mtu << 4) | dev->sm_sl;
	pip->vlcap_inittype = 0x10;	/* VLCap = VL0, InitType = 0 */
	pip->vl_high_limit = dev->vl_high_limit;
	/* pip->vl_arb_high_cap; // only one VL */
	/* pip->vl_arb_low_cap; // only one VL */
	/* InitTypeReply = 0 */
	/* our mtu cap depends on whether 4K MTU enabled or not */
	pip->inittypereply_mtucap = ipath_mtu4096 ? IB_MTU_4096 : IB_MTU_2048;
	/* HCAs ignore VLStallCount and HOQLife */
	/* pip->vlstallcnt_hoqlife; */
	pip->operationalvl_pei_peo_fpi_fpo = 0x10;	/* OVLs = 1 */
	pip->mkey_violations = cpu_to_be16(dev->mkey_violations);
	/* P_KeyViolations are counted by hardware. */
	pip->pkey_violations =
		cpu_to_be16((ipath_get_cr_errpkey(dd) -
			     dev->z_pkey_violations) & 0xFFFF);
	pip->qkey_violations = cpu_to_be16(dev->qkey_violations);
	/* Only the hardware GUID is supported for now */
	pip->guid_cap = 1;
	pip->clientrereg_resv_subnetto = dev->subnet_timeout;
	/* 32.768 usec. response time (guessing) */
	pip->resv_resptimevalue = 3;
	pip->localphyerrors_overrunerrors =
		(get_phyerrthreshold(dd) << 4) |
		get_overrunthreshold(dd);
	/* pip->max_credit_hint; */
	if (dev->port_cap_flags & IB_PORT_LINK_LATENCY_SUP) {
		u32 v;

		v = dd->ipath_f_get_ib_cfg(dd, IPATH_IB_CFG_LINKLATENCY);
		pip->link_roundtrip_latency[0] = v >> 16;
		pip->link_roundtrip_latency[1] = v >> 8;
		pip->link_roundtrip_latency[2] = v;
	}

	ret = reply(smp);

bail:
	return ret;
}