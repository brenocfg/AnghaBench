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
typedef  int u32 ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 int IB_WC_BAD_RESP_ERR ; 
 int IB_WC_FATAL_ERR ; 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_INV_EECN_ERR ; 
 int IB_WC_INV_EEC_STATE_ERR ; 
 int IB_WC_LOC_EEC_OP_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 int IB_WC_REM_ABORT_ERR ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_RD_REQ_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 int IB_WC_SUCCESS ; 
 int IB_WC_WR_FLUSH_ERR ; 
 int WC_STATUS_ERROR_BIT ; 
 int WC_STATUS_REMOTE_ERROR_FLAGS ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void map_ib_wc_status(u32 cqe_status,
				    enum ib_wc_status *wc_status)
{
	if (unlikely(cqe_status & WC_STATUS_ERROR_BIT)) {
		switch (cqe_status & 0x3F) {
		case 0x01:
		case 0x21:
			*wc_status = IB_WC_LOC_LEN_ERR;
			break;
		case 0x02:
		case 0x22:
			*wc_status = IB_WC_LOC_QP_OP_ERR;
			break;
		case 0x03:
		case 0x23:
			*wc_status = IB_WC_LOC_EEC_OP_ERR;
			break;
		case 0x04:
		case 0x24:
			*wc_status = IB_WC_LOC_PROT_ERR;
			break;
		case 0x05:
		case 0x25:
			*wc_status = IB_WC_WR_FLUSH_ERR;
			break;
		case 0x06:
			*wc_status = IB_WC_MW_BIND_ERR;
			break;
		case 0x07: /* remote error - look into bits 20:24 */
			switch ((cqe_status
				 & WC_STATUS_REMOTE_ERROR_FLAGS) >> 11) {
			case 0x0:
				/*
				 * PSN Sequence Error!
				 * couldn't find a matching status!
				 */
				*wc_status = IB_WC_GENERAL_ERR;
				break;
			case 0x1:
				*wc_status = IB_WC_REM_INV_REQ_ERR;
				break;
			case 0x2:
				*wc_status = IB_WC_REM_ACCESS_ERR;
				break;
			case 0x3:
				*wc_status = IB_WC_REM_OP_ERR;
				break;
			case 0x4:
				*wc_status = IB_WC_REM_INV_RD_REQ_ERR;
				break;
			}
			break;
		case 0x08:
			*wc_status = IB_WC_RETRY_EXC_ERR;
			break;
		case 0x09:
			*wc_status = IB_WC_RNR_RETRY_EXC_ERR;
			break;
		case 0x0A:
		case 0x2D:
			*wc_status = IB_WC_REM_ABORT_ERR;
			break;
		case 0x0B:
		case 0x2E:
			*wc_status = IB_WC_INV_EECN_ERR;
			break;
		case 0x0C:
		case 0x2F:
			*wc_status = IB_WC_INV_EEC_STATE_ERR;
			break;
		case 0x0D:
			*wc_status = IB_WC_BAD_RESP_ERR;
			break;
		case 0x10:
			/* WQE purged */
			*wc_status = IB_WC_WR_FLUSH_ERR;
			break;
		default:
			*wc_status = IB_WC_FATAL_ERR;

		}
	} else
		*wc_status = IB_WC_SUCCESS;
}