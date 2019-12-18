#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ib_smp {int dummy; } ;
struct TYPE_2__ {int class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; } ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 136 
#define  IB_MGMT_METHOD_GET_RESP 135 
#define  IB_MGMT_METHOD_SET 134 
#define  IB_PMA_CLASS_PORT_INFO 133 
#define  IB_PMA_PORT_COUNTERS 132 
#define  IB_PMA_PORT_COUNTERS_EXT 131 
#define  IB_PMA_PORT_SAMPLES_CONTROL 130 
#define  IB_PMA_PORT_SAMPLES_RESULT 129 
#define  IB_PMA_PORT_SAMPLES_RESULT_EXT 128 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
 int recv_pma_get_classportinfo (struct ib_pma_mad*) ; 
 int recv_pma_get_portcounters (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_pma_get_portcounters_ext (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_pma_get_portsamplescontrol (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_pma_get_portsamplesresult (struct ib_pma_mad*,struct ib_device*) ; 
 int recv_pma_get_portsamplesresult_ext (struct ib_pma_mad*,struct ib_device*) ; 
 int recv_pma_set_portcounters (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_pma_set_portcounters_ext (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int recv_pma_set_portsamplescontrol (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int reply (struct ib_smp*) ; 

__attribute__((used)) static int process_perf(struct ib_device *ibdev, u8 port_num,
			struct ib_mad *in_mad,
			struct ib_mad *out_mad)
{
	struct ib_pma_mad *pmp = (struct ib_pma_mad *)out_mad;
	int ret;

	*out_mad = *in_mad;
	if (pmp->mad_hdr.class_version != 1) {
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		ret = reply((struct ib_smp *) pmp);
		goto bail;
	}

	switch (pmp->mad_hdr.method) {
	case IB_MGMT_METHOD_GET:
		switch (pmp->mad_hdr.attr_id) {
		case IB_PMA_CLASS_PORT_INFO:
			ret = recv_pma_get_classportinfo(pmp);
			goto bail;
		case IB_PMA_PORT_SAMPLES_CONTROL:
			ret = recv_pma_get_portsamplescontrol(pmp, ibdev,
							      port_num);
			goto bail;
		case IB_PMA_PORT_SAMPLES_RESULT:
			ret = recv_pma_get_portsamplesresult(pmp, ibdev);
			goto bail;
		case IB_PMA_PORT_SAMPLES_RESULT_EXT:
			ret = recv_pma_get_portsamplesresult_ext(pmp,
								 ibdev);
			goto bail;
		case IB_PMA_PORT_COUNTERS:
			ret = recv_pma_get_portcounters(pmp, ibdev,
							port_num);
			goto bail;
		case IB_PMA_PORT_COUNTERS_EXT:
			ret = recv_pma_get_portcounters_ext(pmp, ibdev,
							    port_num);
			goto bail;
		default:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_smp *) pmp);
			goto bail;
		}

	case IB_MGMT_METHOD_SET:
		switch (pmp->mad_hdr.attr_id) {
		case IB_PMA_PORT_SAMPLES_CONTROL:
			ret = recv_pma_set_portsamplescontrol(pmp, ibdev,
							      port_num);
			goto bail;
		case IB_PMA_PORT_COUNTERS:
			ret = recv_pma_set_portcounters(pmp, ibdev,
							port_num);
			goto bail;
		case IB_PMA_PORT_COUNTERS_EXT:
			ret = recv_pma_set_portcounters_ext(pmp, ibdev,
							    port_num);
			goto bail;
		default:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_smp *) pmp);
			goto bail;
		}

	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		goto bail;
	default:
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METHOD;
		ret = reply((struct ib_smp *) pmp);
	}

bail:
	return ret;
}