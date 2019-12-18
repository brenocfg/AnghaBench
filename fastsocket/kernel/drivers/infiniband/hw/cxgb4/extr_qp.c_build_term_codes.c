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
typedef  int u8 ;
struct t4_cqe {int dummy; } ;

/* Variables and functions */
 int CQE_OPCODE (struct t4_cqe*) ; 
 int CQE_STATUS (struct t4_cqe*) ; 
 int DDPT_BASE_BOUNDS ; 
 int DDPT_INV_VERS ; 
 int DDPU_INV_MO ; 
 int DDPU_INV_MSN_NOBUF ; 
 int DDPU_INV_MSN_RANGE ; 
 int DDPU_INV_QN ; 
 int DDPU_INV_VERS ; 
 int DDPU_MSG_TOOBIG ; 
 int DDP_LLP ; 
 int DDP_LOCAL_CATA ; 
 int DDP_TAGGED_ERR ; 
 int DDP_UNTAGGED_ERR ; 
 int FW_RI_RDMA_WRITE ; 
 int FW_RI_READ_RESP ; 
 int FW_RI_SEND_WITH_INV ; 
 int FW_RI_SEND_WITH_SE_INV ; 
 int LAYER_DDP ; 
 int LAYER_MPA ; 
 int LAYER_RDMAP ; 
 int MPA_CRC_ERR ; 
 int MPA_MARKER_ERR ; 
 int RDMAP_ACC_VIOL ; 
 int RDMAP_BASE_BOUNDS ; 
 int RDMAP_CANT_INV_STAG ; 
 int RDMAP_INV_OPCODE ; 
 int RDMAP_INV_STAG ; 
 int RDMAP_INV_VERS ; 
 int RDMAP_LOCAL_CATA ; 
 int RDMAP_REMOTE_OP ; 
 int RDMAP_REMOTE_PROT ; 
 int RDMAP_STAG_NOT_ASSOC ; 
 int RDMAP_TO_WRAP ; 
 int RQ_TYPE (struct t4_cqe*) ; 
#define  T4_ERR_ACCESS 153 
#define  T4_ERR_BOUND 152 
#define  T4_ERR_CRC 151 
#define  T4_ERR_DDP_QUEUE_NUM 150 
#define  T4_ERR_DDP_VERSION 149 
#define  T4_ERR_ECC 148 
#define  T4_ERR_ECC_PSTAG 147 
#define  T4_ERR_INTERNAL_ERR 146 
#define  T4_ERR_INVALIDATE_MR_WITH_MW_BOUND 145 
#define  T4_ERR_INVALIDATE_SHARED_MR 144 
#define  T4_ERR_IRD_OVERFLOW 143 
#define  T4_ERR_MARKER 142 
#define  T4_ERR_MO 141 
#define  T4_ERR_MSN 140 
#define  T4_ERR_MSN_GAP 139 
#define  T4_ERR_MSN_RANGE 138 
#define  T4_ERR_OPCODE 137 
#define  T4_ERR_OUT_OF_RQE 136 
#define  T4_ERR_PBL_ADDR_BOUND 135 
#define  T4_ERR_PDID 134 
#define  T4_ERR_PDU_LEN_ERR 133 
#define  T4_ERR_QPID 132 
#define  T4_ERR_RDMA_VERSION 131 
#define  T4_ERR_STAG 130 
#define  T4_ERR_TBIT 129 
#define  T4_ERR_WRAP 128 

__attribute__((used)) static inline void build_term_codes(struct t4_cqe *err_cqe, u8 *layer_type,
				    u8 *ecode)
{
	int status;
	int tagged;
	int opcode;
	int rqtype;
	int send_inv;

	if (!err_cqe) {
		*layer_type = LAYER_RDMAP|DDP_LOCAL_CATA;
		*ecode = 0;
		return;
	}

	status = CQE_STATUS(err_cqe);
	opcode = CQE_OPCODE(err_cqe);
	rqtype = RQ_TYPE(err_cqe);
	send_inv = (opcode == FW_RI_SEND_WITH_INV) ||
		   (opcode == FW_RI_SEND_WITH_SE_INV);
	tagged = (opcode == FW_RI_RDMA_WRITE) ||
		 (rqtype && (opcode == FW_RI_READ_RESP));

	switch (status) {
	case T4_ERR_STAG:
		if (send_inv) {
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
			*ecode = RDMAP_CANT_INV_STAG;
		} else {
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
			*ecode = RDMAP_INV_STAG;
		}
		break;
	case T4_ERR_PDID:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		if ((opcode == FW_RI_SEND_WITH_INV) ||
		    (opcode == FW_RI_SEND_WITH_SE_INV))
			*ecode = RDMAP_CANT_INV_STAG;
		else
			*ecode = RDMAP_STAG_NOT_ASSOC;
		break;
	case T4_ERR_QPID:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_STAG_NOT_ASSOC;
		break;
	case T4_ERR_ACCESS:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_ACC_VIOL;
		break;
	case T4_ERR_WRAP:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_TO_WRAP;
		break;
	case T4_ERR_BOUND:
		if (tagged) {
			*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
			*ecode = DDPT_BASE_BOUNDS;
		} else {
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
			*ecode = RDMAP_BASE_BOUNDS;
		}
		break;
	case T4_ERR_INVALIDATE_SHARED_MR:
	case T4_ERR_INVALIDATE_MR_WITH_MW_BOUND:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_CANT_INV_STAG;
		break;
	case T4_ERR_ECC:
	case T4_ERR_ECC_PSTAG:
	case T4_ERR_INTERNAL_ERR:
		*layer_type = LAYER_RDMAP|RDMAP_LOCAL_CATA;
		*ecode = 0;
		break;
	case T4_ERR_OUT_OF_RQE:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MSN_NOBUF;
		break;
	case T4_ERR_PBL_ADDR_BOUND:
		*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
		*ecode = DDPT_BASE_BOUNDS;
		break;
	case T4_ERR_CRC:
		*layer_type = LAYER_MPA|DDP_LLP;
		*ecode = MPA_CRC_ERR;
		break;
	case T4_ERR_MARKER:
		*layer_type = LAYER_MPA|DDP_LLP;
		*ecode = MPA_MARKER_ERR;
		break;
	case T4_ERR_PDU_LEN_ERR:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_MSG_TOOBIG;
		break;
	case T4_ERR_DDP_VERSION:
		if (tagged) {
			*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
			*ecode = DDPT_INV_VERS;
		} else {
			*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
			*ecode = DDPU_INV_VERS;
		}
		break;
	case T4_ERR_RDMA_VERSION:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_INV_VERS;
		break;
	case T4_ERR_OPCODE:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_INV_OPCODE;
		break;
	case T4_ERR_DDP_QUEUE_NUM:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_QN;
		break;
	case T4_ERR_MSN:
	case T4_ERR_MSN_GAP:
	case T4_ERR_MSN_RANGE:
	case T4_ERR_IRD_OVERFLOW:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MSN_RANGE;
		break;
	case T4_ERR_TBIT:
		*layer_type = LAYER_DDP|DDP_LOCAL_CATA;
		*ecode = 0;
		break;
	case T4_ERR_MO:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MO;
		break;
	default:
		*layer_type = LAYER_RDMAP|DDP_LOCAL_CATA;
		*ecode = 0;
		break;
	}
}