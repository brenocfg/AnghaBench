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
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int C2_QP_STATE_CLOSING ; 
 int C2_QP_STATE_ERROR ; 
 int C2_QP_STATE_IDLE ; 
 int C2_QP_STATE_RTS ; 
#define  IB_QPS_ERR 132 
#define  IB_QPS_RESET 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 

__attribute__((used)) static int to_c2_state(enum ib_qp_state ib_state)
{
	switch (ib_state) {
	case IB_QPS_RESET:
		return C2_QP_STATE_IDLE;
	case IB_QPS_RTS:
		return C2_QP_STATE_RTS;
	case IB_QPS_SQD:
		return C2_QP_STATE_CLOSING;
	case IB_QPS_SQE:
		return C2_QP_STATE_CLOSING;
	case IB_QPS_ERR:
		return C2_QP_STATE_ERROR;
	default:
		return -1;
	}
}