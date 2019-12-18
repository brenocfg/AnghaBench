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
typedef  enum ehca_qp_state { ____Placeholder_ehca_qp_state } ehca_qp_state ;

/* Variables and functions */
 int EHCA_QPS_ERR ; 
 int EHCA_QPS_INIT ; 
 int EHCA_QPS_RESET ; 
 int EHCA_QPS_RTR ; 
 int EHCA_QPS_RTS ; 
 int EHCA_QPS_SQD ; 
 int EHCA_QPS_SQE ; 
 int EINVAL ; 
#define  IB_QPS_ERR 134 
#define  IB_QPS_INIT 133 
#define  IB_QPS_RESET 132 
#define  IB_QPS_RTR 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 

__attribute__((used)) static inline enum ehca_qp_state ib2ehca_qp_state(enum ib_qp_state ib_qp_state)
{
	switch (ib_qp_state) {
	case IB_QPS_RESET:
		return EHCA_QPS_RESET;
	case IB_QPS_INIT:
		return EHCA_QPS_INIT;
	case IB_QPS_RTR:
		return EHCA_QPS_RTR;
	case IB_QPS_RTS:
		return EHCA_QPS_RTS;
	case IB_QPS_SQD:
		return EHCA_QPS_SQD;
	case IB_QPS_SQE:
		return EHCA_QPS_SQE;
	case IB_QPS_ERR:
		return EHCA_QPS_ERR;
	default:
		ehca_gen_err("invalid ib_qp_state=%x", ib_qp_state);
		return -EINVAL;
	}
}