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
struct ipath_ibdev {int mkeyprot; scalar_t__ mkey; int mkey_violations; int mkey_lease_period; int port_cap_flags; scalar_t__ mkey_lease_timeout; } ;
struct ib_smp {int class_version; scalar_t__ mkey; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; } ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int IB_MAD_IGNORE_MKEY ; 
 int IB_MAD_RESULT_CONSUMED ; 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 140 
#define  IB_MGMT_METHOD_GET_RESP 139 
#define  IB_MGMT_METHOD_REPORT 138 
#define  IB_MGMT_METHOD_REPORT_RESP 137 
#define  IB_MGMT_METHOD_SET 136 
#define  IB_MGMT_METHOD_TRAP 135 
#define  IB_MGMT_METHOD_TRAP_REPRESS 134 
 int IB_PORT_SM ; 
 int IB_PORT_SM_DISABLED ; 
#define  IB_SMP_ATTR_GUID_INFO 133 
#define  IB_SMP_ATTR_NODE_DESC 132 
#define  IB_SMP_ATTR_NODE_INFO 131 
#define  IB_SMP_ATTR_PKEY_TABLE 130 
#define  IB_SMP_ATTR_PORT_INFO 129 
#define  IB_SMP_ATTR_SM_INFO 128 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
 scalar_t__ jiffies ; 
 int recv_subn_get_guidinfo (struct ib_smp*,struct ib_device*) ; 
 int recv_subn_get_nodedescription (struct ib_smp*,struct ib_device*) ; 
 int recv_subn_get_nodeinfo (struct ib_smp*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_subn_get_pkeytable (struct ib_smp*,struct ib_device*) ; 
 int recv_subn_get_portinfo (struct ib_smp*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_subn_set_guidinfo (struct ib_smp*,struct ib_device*) ; 
 int recv_subn_set_pkeytable (struct ib_smp*,struct ib_device*) ; 
 int recv_subn_set_portinfo (struct ib_smp*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int reply (struct ib_smp*) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 
 struct ipath_ibdev* to_idev (struct ib_device*) ; 

__attribute__((used)) static int process_subn(struct ib_device *ibdev, int mad_flags,
			u8 port_num, struct ib_mad *in_mad,
			struct ib_mad *out_mad)
{
	struct ib_smp *smp = (struct ib_smp *)out_mad;
	struct ipath_ibdev *dev = to_idev(ibdev);
	int ret;

	*out_mad = *in_mad;
	if (smp->class_version != 1) {
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply(smp);
		goto bail;
	}

	/* Is the mkey in the process of expiring? */
	if (dev->mkey_lease_timeout &&
	    time_after_eq(jiffies, dev->mkey_lease_timeout)) {
		/* Clear timeout and mkey protection field. */
		dev->mkey_lease_timeout = 0;
		dev->mkeyprot = 0;
	}

	/*
	 * M_Key checking depends on
	 * Portinfo:M_Key_protect_bits
	 */
	if ((mad_flags & IB_MAD_IGNORE_MKEY) == 0 && dev->mkey != 0 &&
	    dev->mkey != smp->mkey &&
	    (smp->method == IB_MGMT_METHOD_SET ||
	     (smp->method == IB_MGMT_METHOD_GET &&
	      dev->mkeyprot >= 2))) {
		if (dev->mkey_violations != 0xFFFF)
			++dev->mkey_violations;
		if (dev->mkey_lease_timeout ||
		    dev->mkey_lease_period == 0) {
			ret = IB_MAD_RESULT_SUCCESS |
				IB_MAD_RESULT_CONSUMED;
			goto bail;
		}
		dev->mkey_lease_timeout = jiffies +
			dev->mkey_lease_period * HZ;
		/* Future: Generate a trap notice. */
		ret = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		goto bail;
	} else if (dev->mkey_lease_timeout)
		dev->mkey_lease_timeout = 0;

	switch (smp->method) {
	case IB_MGMT_METHOD_GET:
		switch (smp->attr_id) {
		case IB_SMP_ATTR_NODE_DESC:
			ret = recv_subn_get_nodedescription(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_NODE_INFO:
			ret = recv_subn_get_nodeinfo(smp, ibdev, port_num);
			goto bail;
		case IB_SMP_ATTR_GUID_INFO:
			ret = recv_subn_get_guidinfo(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_PORT_INFO:
			ret = recv_subn_get_portinfo(smp, ibdev, port_num);
			goto bail;
		case IB_SMP_ATTR_PKEY_TABLE:
			ret = recv_subn_get_pkeytable(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_SM_INFO:
			if (dev->port_cap_flags & IB_PORT_SM_DISABLED) {
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				goto bail;
			}
			if (dev->port_cap_flags & IB_PORT_SM) {
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
			ret = recv_subn_set_guidinfo(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_PORT_INFO:
			ret = recv_subn_set_portinfo(smp, ibdev, port_num);
			goto bail;
		case IB_SMP_ATTR_PKEY_TABLE:
			ret = recv_subn_set_pkeytable(smp, ibdev);
			goto bail;
		case IB_SMP_ATTR_SM_INFO:
			if (dev->port_cap_flags & IB_PORT_SM_DISABLED) {
				ret = IB_MAD_RESULT_SUCCESS |
					IB_MAD_RESULT_CONSUMED;
				goto bail;
			}
			if (dev->port_cap_flags & IB_PORT_SM) {
				ret = IB_MAD_RESULT_SUCCESS;
				goto bail;
			}
			/* FALLTHROUGH */
		default:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply(smp);
			goto bail;
		}

	case IB_MGMT_METHOD_TRAP:
	case IB_MGMT_METHOD_REPORT:
	case IB_MGMT_METHOD_REPORT_RESP:
	case IB_MGMT_METHOD_TRAP_REPRESS:
	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		goto bail;
	default:
		smp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply(smp);
	}

bail:
	return ret;
}