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
struct rds_message {int dummy; } ;

/* Variables and functions */
#define  IB_WC_REM_ACCESS_ERR 130 
#define  IB_WC_SUCCESS 129 
#define  IB_WC_WR_FLUSH_ERR 128 
 int RDS_RDMA_OTHER_ERROR ; 
 int RDS_RDMA_REMOTE_ERROR ; 
 int RDS_RDMA_SUCCESS ; 

__attribute__((used)) static void rds_ib_send_complete(struct rds_message *rm,
				 int wc_status,
				 void (*complete)(struct rds_message *rm, int status))
{
	int notify_status;

	switch (wc_status) {
	case IB_WC_WR_FLUSH_ERR:
		return;

	case IB_WC_SUCCESS:
		notify_status = RDS_RDMA_SUCCESS;
		break;

	case IB_WC_REM_ACCESS_ERR:
		notify_status = RDS_RDMA_REMOTE_ERROR;
		break;

	default:
		notify_status = RDS_RDMA_OTHER_ERROR;
		break;
	}
	complete(rm, notify_status);
}