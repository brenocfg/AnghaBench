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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int qp_type; } ;
struct ipath_qp {size_t state; TYPE_1__ ibqp; } ;
struct ipath_ibdev {int /*<<< orphan*/  n_pkt_drops; } ;
struct ipath_ib_header {int dummy; } ;

/* Variables and functions */
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int IPATH_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  ib_ipath_disable_sma ; 
 int* ib_ipath_state_ops ; 
 int /*<<< orphan*/  ipath_rc_rcv (struct ipath_ibdev*,struct ipath_ib_header*,int,void*,int /*<<< orphan*/ ,struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_uc_rcv (struct ipath_ibdev*,struct ipath_ib_header*,int,void*,int /*<<< orphan*/ ,struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_ud_rcv (struct ipath_ibdev*,struct ipath_ib_header*,int,void*,int /*<<< orphan*/ ,struct ipath_qp*) ; 

__attribute__((used)) static void ipath_qp_rcv(struct ipath_ibdev *dev,
			 struct ipath_ib_header *hdr, int has_grh,
			 void *data, u32 tlen, struct ipath_qp *qp)
{
	/* Check for valid receive state. */
	if (!(ib_ipath_state_ops[qp->state] & IPATH_PROCESS_RECV_OK)) {
		dev->n_pkt_drops++;
		return;
	}

	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
	case IB_QPT_GSI:
		if (ib_ipath_disable_sma)
			break;
		/* FALLTHROUGH */
	case IB_QPT_UD:
		ipath_ud_rcv(dev, hdr, has_grh, data, tlen, qp);
		break;

	case IB_QPT_RC:
		ipath_rc_rcv(dev, hdr, has_grh, data, tlen, qp);
		break;

	case IB_QPT_UC:
		ipath_uc_rcv(dev, hdr, has_grh, data, tlen, qp);
		break;

	default:
		break;
	}
}