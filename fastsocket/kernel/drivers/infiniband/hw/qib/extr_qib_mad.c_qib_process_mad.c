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
struct qib_pportdata {int /*<<< orphan*/  congestion_entries_shadow; } ;
struct qib_ibport {int dummy; } ;
struct ib_wc {int dummy; } ;
struct TYPE_2__ {int mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_CLASS_CONG_MGMT 131 
#define  IB_MGMT_CLASS_PERF_MGMT 130 
#define  IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE 129 
#define  IB_MGMT_CLASS_SUBN_LID_ROUTED 128 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int process_cc (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_mad*,struct ib_mad*) ; 
 int process_perf (struct ib_device*,int /*<<< orphan*/ ,struct ib_mad*,struct ib_mad*) ; 
 int process_subn (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_mad*,struct ib_mad*) ; 
 int /*<<< orphan*/  qib_cc_table_size ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

int qib_process_mad(struct ib_device *ibdev, int mad_flags, u8 port,
		    struct ib_wc *in_wc, struct ib_grh *in_grh,
		    struct ib_mad *in_mad, struct ib_mad *out_mad)
{
	int ret;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);

	switch (in_mad->mad_hdr.mgmt_class) {
	case IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE:
	case IB_MGMT_CLASS_SUBN_LID_ROUTED:
		ret = process_subn(ibdev, mad_flags, port, in_mad, out_mad);
		goto bail;

	case IB_MGMT_CLASS_PERF_MGMT:
		ret = process_perf(ibdev, port, in_mad, out_mad);
		goto bail;

	case IB_MGMT_CLASS_CONG_MGMT:
		if (!ppd->congestion_entries_shadow ||
			 !qib_cc_table_size) {
			ret = IB_MAD_RESULT_SUCCESS;
			goto bail;
		}
		ret = process_cc(ibdev, mad_flags, port, in_mad, out_mad);
		goto bail;

	default:
		ret = IB_MAD_RESULT_SUCCESS;
	}

bail:
	return ret;
}