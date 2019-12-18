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
typedef  enum ib_qp_statetrans { ____Placeholder_ib_qp_statetrans } ib_qp_statetrans ;

/* Variables and functions */
 int EINVAL ; 
 int IB_QPST_ANY2ERR ; 
 int IB_QPST_ANY2RESET ; 
 int IB_QPST_INIT2INIT ; 
 int IB_QPST_INIT2RTR ; 
 int IB_QPST_RESET2INIT ; 
 int IB_QPST_RTR2RTS ; 
 int IB_QPST_RTS2RTS ; 
 int IB_QPST_RTS2SQD ; 
 int IB_QPST_SQD2RTS ; 
 int IB_QPST_SQE2RTS ; 
#define  IB_QPS_ERR 134 
#define  IB_QPS_INIT 133 
#define  IB_QPS_RESET 132 
#define  IB_QPS_RTR 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 

__attribute__((used)) static inline enum ib_qp_statetrans get_modqp_statetrans(int ib_fromstate,
							 int ib_tostate)
{
	int index = -EINVAL;
	switch (ib_tostate) {
	case IB_QPS_RESET:
		index = IB_QPST_ANY2RESET;
		break;
	case IB_QPS_INIT:
		switch (ib_fromstate) {
		case IB_QPS_RESET:
			index = IB_QPST_RESET2INIT;
			break;
		case IB_QPS_INIT:
			index = IB_QPST_INIT2INIT;
			break;
		}
		break;
	case IB_QPS_RTR:
		if (ib_fromstate == IB_QPS_INIT)
			index = IB_QPST_INIT2RTR;
		break;
	case IB_QPS_RTS:
		switch (ib_fromstate) {
		case IB_QPS_RTR:
			index = IB_QPST_RTR2RTS;
			break;
		case IB_QPS_RTS:
			index = IB_QPST_RTS2RTS;
			break;
		case IB_QPS_SQD:
			index = IB_QPST_SQD2RTS;
			break;
		case IB_QPS_SQE:
			index = IB_QPST_SQE2RTS;
			break;
		}
		break;
	case IB_QPS_SQD:
		if (ib_fromstate == IB_QPS_RTS)
			index = IB_QPST_RTS2SQD;
		break;
	case IB_QPS_SQE:
		break;
	case IB_QPS_ERR:
		index = IB_QPST_ANY2ERR;
		break;
	default:
		break;
	}
	return index;
}