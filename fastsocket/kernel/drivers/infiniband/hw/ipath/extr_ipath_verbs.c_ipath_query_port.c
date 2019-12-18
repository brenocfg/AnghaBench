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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u64 ;
typedef  scalar_t__ u16 ;
struct ipath_ibdev {int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  qkey_violations; scalar_t__ z_pkey_violations; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; struct ipath_devdata* dd; } ;
struct ipath_devdata {size_t ipath_lastibcstat; size_t ibcs_lts_mask; int ipath_ibmtu; int /*<<< orphan*/  ipath_link_speed_active; int /*<<< orphan*/  ipath_link_width_active; int /*<<< orphan*/  ipath_lmc; scalar_t__ ipath_lid; } ;
struct ib_port_attr {int gid_tbl_len; int max_msg_sz; int max_vl_num; int active_mtu; int /*<<< orphan*/  subnet_timeout; void* max_mtu; scalar_t__ init_type_reply; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  qkey_viol_cntr; scalar_t__ bad_pkey_cntr; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  phys_state; scalar_t__ state; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lmc; scalar_t__ lid; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int IB_MTU_1024 ; 
 void* IB_MTU_2048 ; 
 int IB_MTU_256 ; 
 void* IB_MTU_4096 ; 
 int IB_MTU_512 ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipath_cvt_physportstate ; 
 scalar_t__ ipath_get_cr_errpkey (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_get_npkeys (struct ipath_devdata*) ; 
 scalar_t__ ipath_ib_linkstate (struct ipath_devdata*,size_t) ; 
 scalar_t__ ipath_mtu4096 ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int ipath_query_port(struct ib_device *ibdev,
			    u8 port, struct ib_port_attr *props)
{
	struct ipath_ibdev *dev = to_idev(ibdev);
	struct ipath_devdata *dd = dev->dd;
	enum ib_mtu mtu;
	u16 lid = dd->ipath_lid;
	u64 ibcstat;

	memset(props, 0, sizeof(*props));
	props->lid = lid ? lid : be16_to_cpu(IB_LID_PERMISSIVE);
	props->lmc = dd->ipath_lmc;
	props->sm_lid = dev->sm_lid;
	props->sm_sl = dev->sm_sl;
	ibcstat = dd->ipath_lastibcstat;
	/* map LinkState to IB portinfo values.  */
	props->state = ipath_ib_linkstate(dd, ibcstat) + 1;

	/* See phys_state_show() */
	props->phys_state = /* MEA: assumes shift == 0 */
		ipath_cvt_physportstate[dd->ipath_lastibcstat &
		dd->ibcs_lts_mask];
	props->port_cap_flags = dev->port_cap_flags;
	props->gid_tbl_len = 1;
	props->max_msg_sz = 0x80000000;
	props->pkey_tbl_len = ipath_get_npkeys(dd);
	props->bad_pkey_cntr = ipath_get_cr_errpkey(dd) -
		dev->z_pkey_violations;
	props->qkey_viol_cntr = dev->qkey_violations;
	props->active_width = dd->ipath_link_width_active;
	/* See rate_show() */
	props->active_speed = dd->ipath_link_speed_active;
	props->max_vl_num = 1;		/* VLCap = VL0 */
	props->init_type_reply = 0;

	props->max_mtu = ipath_mtu4096 ? IB_MTU_4096 : IB_MTU_2048;
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
	default:
		mtu = IB_MTU_2048;
	}
	props->active_mtu = mtu;
	props->subnet_timeout = dev->subnet_timeout;

	return 0;
}