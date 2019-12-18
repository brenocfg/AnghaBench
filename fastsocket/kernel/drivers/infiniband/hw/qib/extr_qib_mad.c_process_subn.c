#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct qib_pportdata {TYPE_2__* dd; } ;
struct qib_ibport {int port_cap_flags; } ;
struct ib_smp {int class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/ * data; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  attr_mod; } ;
struct TYPE_3__ {scalar_t__ attr_id; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_device {scalar_t__ phys_port_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IB_MAD_RESULT_CONSUMED ; 
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 143 
#define  IB_MGMT_METHOD_GET_RESP 142 
#define  IB_MGMT_METHOD_REPORT 141 
#define  IB_MGMT_METHOD_REPORT_RESP 140 
#define  IB_MGMT_METHOD_SEND 139 
#define  IB_MGMT_METHOD_SET 138 
#define  IB_MGMT_METHOD_TRAP 137 
#define  IB_MGMT_METHOD_TRAP_REPRESS 136 
 int IB_PORT_SM ; 
 int IB_PORT_SM_DISABLED ; 
#define  IB_SMP_ATTR_GUID_INFO 135 
#define  IB_SMP_ATTR_NODE_DESC 134 
#define  IB_SMP_ATTR_NODE_INFO 133 
 int /*<<< orphan*/  IB_SMP_ATTR_NOTICE ; 
#define  IB_SMP_ATTR_PKEY_TABLE 132 
#define  IB_SMP_ATTR_PORT_INFO 131 
#define  IB_SMP_ATTR_SL_TO_VL_TABLE 130 
#define  IB_SMP_ATTR_SM_INFO 129 
#define  IB_SMP_ATTR_VL_ARB_TABLE 128 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
 int /*<<< orphan*/  QIB_IB_CFG_PORT ; 
 int /*<<< orphan*/  QIB_VENDOR_IPG ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int check_mkey (struct qib_ibport*,struct ib_smp*,int) ; 
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int reply (struct ib_smp*) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int subn_get_guidinfo (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_get_nodedescription (struct ib_smp*,struct ib_device*) ; 
 int subn_get_nodeinfo (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_get_pkeytable (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_get_portinfo (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_get_sl_to_vl (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_get_vl_arb (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_set_guidinfo (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_set_pkeytable (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_set_portinfo (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_set_sl_to_vl (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_set_vl_arb (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 int subn_trap_repress (struct ib_smp*,struct ib_device*,scalar_t__) ; 
 struct qib_ibport* to_iport (struct ib_device*,scalar_t__) ; 

__attribute__((used)) static int process_subn(struct ib_device *ibdev, int mad_flags,
			u8 port, struct ib_mad *in_mad,
			struct ib_mad *out_mad)
{
	struct ib_smp *smp = (struct ib_smp *)out_mad;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	int ret;

	*out_mad = *in_mad;
	if (smp->class_version != 1) {
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply(smp);
		goto bail;
	}

	ret = check_mkey(ibp, smp, mad_flags);
	if (ret) {
		u32 port_num = be32_to_cpu(smp->attr_mod);

		/*
		 * If this is a get/set portinfo, we already check the
		 * M_Key if the MAD is for another port and the M_Key
		 * is OK on the receiving port. This check is needed
		 * to increment the error counters when the M_Key
		 * fails to match on *both* ports.
		 */
		if (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    port_num && port_num <= ibdev->phys_port_cnt &&
		    port != port_num)
			(void) check_mkey(to_iport(ibdev, port_num), smp, 0);
		ret = IB_MAD_RESULT_FAILURE;
		goto bail;
	}

	switch (smp->method) {
	case IB_MGMT_METHOD_GET:
		switch (smp->attr_id) {
		case IB_SMP_ATTR_NODE_DESC:
			ret = subn_get_nodedescription(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_NODE_INFO:
			ret = subn_get_nodeinfo(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_GUID_INFO:
			ret = subn_get_guidinfo(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_PORT_INFO:
			ret = subn_get_portinfo(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_PKEY_TABLE:
			ret = subn_get_pkeytable(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_SL_TO_VL_TABLE:
			ret = subn_get_sl_to_vl(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_VL_ARB_TABLE:
			ret = subn_get_vl_arb(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_SM_INFO:
			if (ibp->port_cap_flags & IB_PORT_SM_DISABLED) {
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				goto bail;
			}
			if (ibp->port_cap_flags & IB_PORT_SM) {
				ret = IB_MAD_RESULT_SUCCESS;
				goto bail;
			}
			/* FALLTHROUGH */
		default:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
			goto bail;
		}

	case IB_MGMT_METHOD_SET:
		switch (smp->attr_id) {
		case IB_SMP_ATTR_GUID_INFO:
			ret = subn_set_guidinfo(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_PORT_INFO:
			ret = subn_set_portinfo(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_PKEY_TABLE:
			ret = subn_set_pkeytable(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_SL_TO_VL_TABLE:
			ret = subn_set_sl_to_vl(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_VL_ARB_TABLE:
			ret = subn_set_vl_arb(smp, ibdev, port);
			goto bail;
		case IB_SMP_ATTR_SM_INFO:
			if (ibp->port_cap_flags & IB_PORT_SM_DISABLED) {
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				goto bail;
			}
			if (ibp->port_cap_flags & IB_PORT_SM) {
				ret = IB_MAD_RESULT_SUCCESS;
				goto bail;
			}
			/* FALLTHROUGH */
		default:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
			goto bail;
		}

	case IB_MGMT_METHOD_TRAP_REPRESS:
		if (smp->attr_id == IB_SMP_ATTR_NOTICE)
			ret = subn_trap_repress(smp, ibdev, port);
		else {
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
		}
		goto bail;

	case IB_MGMT_METHOD_TRAP:
	case IB_MGMT_METHOD_REPORT:
	case IB_MGMT_METHOD_REPORT_RESP:
	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		goto bail;

	case IB_MGMT_METHOD_SEND:
		if (ib_get_smp_direction(smp) &&
		    smp->attr_id == QIB_VENDOR_IPG) {
			ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PORT,
					      smp->data[0]);
			ret = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		} else
			ret = IB_MAD_RESULT_SUCCESS;
		goto bail;

	default:
		smp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply(smp);
	}

bail:
	return ret;
}