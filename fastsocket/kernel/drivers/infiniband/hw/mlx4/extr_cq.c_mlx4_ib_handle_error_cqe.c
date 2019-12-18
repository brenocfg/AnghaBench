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
struct mlx4_err_cqe {int syndrome; int owner_sr_opcode; int /*<<< orphan*/  vendor_err_syndrome; int /*<<< orphan*/  wqe_index; int /*<<< orphan*/  my_qpn; } ;
struct ib_wc {int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_BAD_RESP_ERR ; 
 int /*<<< orphan*/  IB_WC_GENERAL_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_LEN_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_PROT_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_MW_BIND_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ABORT_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_INV_REQ_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_RNR_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int MLX4_CQE_OWNER_MASK ; 
#define  MLX4_CQE_SYNDROME_BAD_RESP_ERR 140 
#define  MLX4_CQE_SYNDROME_LOCAL_ACCESS_ERR 139 
#define  MLX4_CQE_SYNDROME_LOCAL_LENGTH_ERR 138 
#define  MLX4_CQE_SYNDROME_LOCAL_PROT_ERR 137 
#define  MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR 136 
#define  MLX4_CQE_SYNDROME_MW_BIND_ERR 135 
#define  MLX4_CQE_SYNDROME_REMOTE_ABORTED_ERR 134 
#define  MLX4_CQE_SYNDROME_REMOTE_ACCESS_ERR 133 
#define  MLX4_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR 132 
#define  MLX4_CQE_SYNDROME_REMOTE_OP_ERR 131 
#define  MLX4_CQE_SYNDROME_RNR_RETRY_EXC_ERR 130 
#define  MLX4_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR 129 
#define  MLX4_CQE_SYNDROME_WR_FLUSH_ERR 128 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_cqe (struct mlx4_err_cqe*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx4_ib_handle_error_cqe(struct mlx4_err_cqe *cqe,
				     struct ib_wc *wc)
{
	if (cqe->syndrome == MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR) {
		pr_debug("local QP operation err "
		       "(QPN %06x, WQE index %x, vendor syndrome %02x, "
		       "opcode = %02x)\n",
		       be32_to_cpu(cqe->my_qpn), be16_to_cpu(cqe->wqe_index),
		       cqe->vendor_err_syndrome,
		       cqe->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK);
		dump_cqe(cqe);
	}

	switch (cqe->syndrome) {
	case MLX4_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		wc->status = IB_WC_LOC_LEN_ERR;
		break;
	case MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		wc->status = IB_WC_LOC_QP_OP_ERR;
		break;
	case MLX4_CQE_SYNDROME_LOCAL_PROT_ERR:
		wc->status = IB_WC_LOC_PROT_ERR;
		break;
	case MLX4_CQE_SYNDROME_WR_FLUSH_ERR:
		wc->status = IB_WC_WR_FLUSH_ERR;
		break;
	case MLX4_CQE_SYNDROME_MW_BIND_ERR:
		wc->status = IB_WC_MW_BIND_ERR;
		break;
	case MLX4_CQE_SYNDROME_BAD_RESP_ERR:
		wc->status = IB_WC_BAD_RESP_ERR;
		break;
	case MLX4_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		wc->status = IB_WC_LOC_ACCESS_ERR;
		break;
	case MLX4_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		wc->status = IB_WC_REM_INV_REQ_ERR;
		break;
	case MLX4_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		wc->status = IB_WC_REM_ACCESS_ERR;
		break;
	case MLX4_CQE_SYNDROME_REMOTE_OP_ERR:
		wc->status = IB_WC_REM_OP_ERR;
		break;
	case MLX4_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		wc->status = IB_WC_RETRY_EXC_ERR;
		break;
	case MLX4_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		wc->status = IB_WC_RNR_RETRY_EXC_ERR;
		break;
	case MLX4_CQE_SYNDROME_REMOTE_ABORTED_ERR:
		wc->status = IB_WC_REM_ABORT_ERR;
		break;
	default:
		wc->status = IB_WC_GENERAL_ERR;
		break;
	}

	wc->vendor_err = cqe->vendor_err_syndrome;
}