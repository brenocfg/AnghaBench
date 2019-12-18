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
typedef  enum c2_qp_state { ____Placeholder_c2_qp_state } c2_qp_state ;

/* Variables and functions */
#define  C2_QP_STATE_CLOSING 133 
#define  C2_QP_STATE_CONNECTING 132 
#define  C2_QP_STATE_ERROR 131 
#define  C2_QP_STATE_IDLE 130 
#define  C2_QP_STATE_RTS 129 
#define  C2_QP_STATE_TERMINATE 128 
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 

__attribute__((used)) static int to_ib_state(enum c2_qp_state c2_state)
{
	switch (c2_state) {
	case C2_QP_STATE_IDLE:
		return IB_QPS_RESET;
	case C2_QP_STATE_CONNECTING:
		return IB_QPS_RTR;
	case C2_QP_STATE_RTS:
		return IB_QPS_RTS;
	case C2_QP_STATE_CLOSING:
		return IB_QPS_SQD;
	case C2_QP_STATE_ERROR:
		return IB_QPS_ERR;
	case C2_QP_STATE_TERMINATE:
		return IB_QPS_SQE;
	default:
		return -1;
	}
}