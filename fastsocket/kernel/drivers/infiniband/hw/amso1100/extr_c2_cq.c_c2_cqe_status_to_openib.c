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
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
#define  C2_OK 133 
#define  CCERR_ACCESS_VIOLATION 132 
#define  CCERR_BASE_AND_BOUNDS_VIOLATION 131 
#define  CCERR_FLUSHED 130 
#define  CCERR_INVALID_WINDOW 129 
#define  CCERR_TOTAL_LENGTH_TOO_BIG 128 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_ACCESS_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 int IB_WC_SUCCESS ; 
 int IB_WC_WR_FLUSH_ERR ; 

__attribute__((used)) static inline enum ib_wc_status c2_cqe_status_to_openib(u8 status)
{
	switch (status) {
	case C2_OK:
		return IB_WC_SUCCESS;
	case CCERR_FLUSHED:
		return IB_WC_WR_FLUSH_ERR;
	case CCERR_BASE_AND_BOUNDS_VIOLATION:
		return IB_WC_LOC_PROT_ERR;
	case CCERR_ACCESS_VIOLATION:
		return IB_WC_LOC_ACCESS_ERR;
	case CCERR_TOTAL_LENGTH_TOO_BIG:
		return IB_WC_LOC_LEN_ERR;
	case CCERR_INVALID_WINDOW:
		return IB_WC_MW_BIND_ERR;
	default:
		return IB_WC_GENERAL_ERR;
	}
}