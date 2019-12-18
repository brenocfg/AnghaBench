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

/* Variables and functions */
#define  C2_OK 152 
#define  CCERR_ACCESS_VIOLATION 151 
#define  CCERR_ADDR_IN_USE 150 
#define  CCERR_ADDR_NOT_AVAIL 149 
#define  CCERR_BASE_AND_BOUNDS_VIOLATION 148 
#define  CCERR_CONN_RESET 147 
#define  CCERR_INSUFFICIENT_RESOURCES 146 
#define  CCERR_INVALID_ADDRESS 145 
#define  CCERR_INVALID_CQ 144 
#define  CCERR_INVALID_EP 143 
#define  CCERR_INVALID_MODIFIER 142 
#define  CCERR_INVALID_MTU 141 
#define  CCERR_INVALID_PD_ID 140 
#define  CCERR_INVALID_QP 139 
#define  CCERR_INVALID_RNIC 138 
#define  CCERR_INVALID_STAG 137 
#define  CCERR_INVALID_WQE 136 
#define  CCERR_MR_IN_USE 135 
#define  CCERR_NOT_IMPLEMENTED 134 
#define  CCERR_NO_BUFS 133 
#define  CCERR_QP_IN_USE 132 
#define  CCERR_QP_NOT_PRIVILEGED 131 
#define  CCERR_STACK_ERROR 130 
#define  CCERR_STAG_STATE_NOT_INVALID 129 
#define  CCERR_ZERO_RDMA_READ_RESOURCES 128 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ECONNRESET ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EPERM ; 
 int EPROTO ; 
 int c2_wr_get_result (void*) ; 

__attribute__((used)) static inline int c2_errno(void *reply)
{
	switch (c2_wr_get_result(reply)) {
	case C2_OK:
		return 0;
	case CCERR_NO_BUFS:
	case CCERR_INSUFFICIENT_RESOURCES:
	case CCERR_ZERO_RDMA_READ_RESOURCES:
		return -ENOMEM;
	case CCERR_MR_IN_USE:
	case CCERR_QP_IN_USE:
		return -EBUSY;
	case CCERR_ADDR_IN_USE:
		return -EADDRINUSE;
	case CCERR_ADDR_NOT_AVAIL:
		return -EADDRNOTAVAIL;
	case CCERR_CONN_RESET:
		return -ECONNRESET;
	case CCERR_NOT_IMPLEMENTED:
	case CCERR_INVALID_WQE:
		return -ENOSYS;
	case CCERR_QP_NOT_PRIVILEGED:
		return -EPERM;
	case CCERR_STACK_ERROR:
		return -EPROTO;
	case CCERR_ACCESS_VIOLATION:
	case CCERR_BASE_AND_BOUNDS_VIOLATION:
		return -EFAULT;
	case CCERR_STAG_STATE_NOT_INVALID:
	case CCERR_INVALID_ADDRESS:
	case CCERR_INVALID_CQ:
	case CCERR_INVALID_EP:
	case CCERR_INVALID_MODIFIER:
	case CCERR_INVALID_MTU:
	case CCERR_INVALID_PD_ID:
	case CCERR_INVALID_QP:
	case CCERR_INVALID_RNIC:
	case CCERR_INVALID_STAG:
		return -EINVAL;
	default:
		return -EAGAIN;
	}
}