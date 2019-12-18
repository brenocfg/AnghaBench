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
#define  EHCA_QPS_ERR 134 
#define  EHCA_QPS_INIT 133 
#define  EHCA_QPS_RESET 132 
#define  EHCA_QPS_RTR 131 
#define  EHCA_QPS_RTS 130 
#define  EHCA_QPS_SQD 129 
#define  EHCA_QPS_SQE 128 
 int EINVAL ; 
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 

__attribute__((used)) static inline enum ib_qp_state ehca2ib_qp_state(enum ehca_qp_state
						ehca_qp_state)
{
	switch (ehca_qp_state) {
	case EHCA_QPS_RESET:
		return IB_QPS_RESET;
	case EHCA_QPS_INIT:
		return IB_QPS_INIT;
	case EHCA_QPS_RTR:
		return IB_QPS_RTR;
	case EHCA_QPS_RTS:
		return IB_QPS_RTS;
	case EHCA_QPS_SQD:
		return IB_QPS_SQD;
	case EHCA_QPS_SQE:
		return IB_QPS_SQE;
	case EHCA_QPS_ERR:
		return IB_QPS_ERR;
	default:
		ehca_gen_err("invalid ehca_qp_state=%x", ehca_qp_state);
		return -EINVAL;
	}
}