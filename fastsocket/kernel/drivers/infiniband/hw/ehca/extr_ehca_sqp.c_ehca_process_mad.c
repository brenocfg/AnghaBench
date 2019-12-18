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
typedef  scalar_t__ u8 ;
struct ib_wc {int /*<<< orphan*/  src_qp; } ;
struct TYPE_2__ {scalar_t__ mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {scalar_t__ phys_port_cnt; } ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_SUCCESS ; 
 scalar_t__ IB_MGMT_CLASS_PERF_MGMT ; 
 int /*<<< orphan*/  ehca_dbg (struct ib_device*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ehca_process_perf (struct ib_device*,scalar_t__,struct ib_wc*,struct ib_grh*,struct ib_mad*,struct ib_mad*) ; 

int ehca_process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
		     struct ib_wc *in_wc, struct ib_grh *in_grh,
		     struct ib_mad *in_mad, struct ib_mad *out_mad)
{
	int ret;

	if (!port_num || port_num > ibdev->phys_port_cnt || !in_wc)
		return IB_MAD_RESULT_FAILURE;

	/* accept only pma request */
	if (in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_PERF_MGMT)
		return IB_MAD_RESULT_SUCCESS;

	ehca_dbg(ibdev, "port_num=%x src_qp=%x", port_num, in_wc->src_qp);
	ret = ehca_process_perf(ibdev, port_num, in_wc, in_grh,
				in_mad, out_mad);

	return ret;
}