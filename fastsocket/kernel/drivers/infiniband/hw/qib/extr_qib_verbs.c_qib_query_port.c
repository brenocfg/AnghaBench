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
typedef  scalar_t__ u16 ;
struct qib_pportdata {int ibmtu; int /*<<< orphan*/  vls_supported; int /*<<< orphan*/  link_speed_active; int /*<<< orphan*/  link_width_active; int /*<<< orphan*/  lastibcstat; int /*<<< orphan*/  lmc; scalar_t__ lid; } ;
struct qib_ibport {int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  qkey_violations; int /*<<< orphan*/  pkey_violations; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; } ;
struct qib_devdata {int /*<<< orphan*/  (* f_ibphys_portstate ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f_iblink_state ) (int /*<<< orphan*/ ) ;} ;
struct ib_port_attr {int max_msg_sz; int active_mtu; int /*<<< orphan*/  subnet_timeout; void* max_mtu; scalar_t__ init_type_reply; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lmc; scalar_t__ lid; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int IB_MTU_1024 ; 
 int IB_MTU_2048 ; 
 int IB_MTU_256 ; 
 void* IB_MTU_4096 ; 
 int IB_MTU_512 ; 
 int /*<<< orphan*/  QIB_GUIDS_PER_PORT ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct qib_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_get_npkeys (struct qib_devdata*) ; 
 void* qib_ibmtu ; 
 int /*<<< orphan*/  qib_num_vls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_query_port(struct ib_device *ibdev, u8 port,
			  struct ib_port_attr *props)
{
	struct qib_devdata *dd = dd_from_ibdev(ibdev);
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	enum ib_mtu mtu;
	u16 lid = ppd->lid;

	memset(props, 0, sizeof(*props));
	props->lid = lid ? lid : be16_to_cpu(IB_LID_PERMISSIVE);
	props->lmc = ppd->lmc;
	props->sm_lid = ibp->sm_lid;
	props->sm_sl = ibp->sm_sl;
	props->state = dd->f_iblink_state(ppd->lastibcstat);
	props->phys_state = dd->f_ibphys_portstate(ppd->lastibcstat);
	props->port_cap_flags = ibp->port_cap_flags;
	props->gid_tbl_len = QIB_GUIDS_PER_PORT;
	props->max_msg_sz = 0x80000000;
	props->pkey_tbl_len = qib_get_npkeys(dd);
	props->bad_pkey_cntr = ibp->pkey_violations;
	props->qkey_viol_cntr = ibp->qkey_violations;
	props->active_width = ppd->link_width_active;
	/* See rate_show() */
	props->active_speed = ppd->link_speed_active;
	props->max_vl_num = qib_num_vls(ppd->vls_supported);
	props->init_type_reply = 0;

	props->max_mtu = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	switch (ppd->ibmtu) {
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
	props->subnet_timeout = ibp->subnet_timeout;

	return 0;
}