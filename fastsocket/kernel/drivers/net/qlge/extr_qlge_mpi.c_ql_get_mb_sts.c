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
struct ql_adapter {int /*<<< orphan*/  ndev; scalar_t__ mailbox_out; } ;
struct mbox_params {int out_count; int /*<<< orphan*/ * mbox_out; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SEM_PROC_REG_MASK ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_read_mpi_reg (struct ql_adapter*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_get_mb_sts(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int i, status;

	status = ql_sem_spinlock(qdev, SEM_PROC_REG_MASK);
	if (status)
		return -EBUSY;
	for (i = 0; i < mbcp->out_count; i++) {
		status =
		    ql_read_mpi_reg(qdev, qdev->mailbox_out + i,
				     &mbcp->mbox_out[i]);
		if (status) {
			netif_err(qdev, drv, qdev->ndev, "Failed mailbox read.\n");
			break;
		}
	}
	ql_sem_unlock(qdev, SEM_PROC_REG_MASK);	/* does flush too */
	return status;
}