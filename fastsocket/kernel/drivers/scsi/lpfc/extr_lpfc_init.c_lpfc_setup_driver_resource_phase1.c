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
struct lpfc_hba {int /*<<< orphan*/  fcf_conn_rec_list; int /*<<< orphan*/  elsbuf; int /*<<< orphan*/  fabric_iocb_list; int /*<<< orphan*/  lpfc_scsi_buf_list_put; int /*<<< orphan*/  scsi_buf_list_put_lock; int /*<<< orphan*/  lpfc_scsi_buf_list_get; int /*<<< orphan*/  scsi_buf_list_get_lock; int /*<<< orphan*/  work_waitq; int /*<<< orphan*/  wait_4_mlo_m_q; int /*<<< orphan*/  work_list; int /*<<< orphan*/  port_list; int /*<<< orphan*/  ndlp_lock; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  fast_event_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_setup_driver_resource_phase1(struct lpfc_hba *phba)
{
	/*
	 * Driver resources common to all SLI revisions
	 */
	atomic_set(&phba->fast_event_count, 0);
	spin_lock_init(&phba->hbalock);

	/* Initialize ndlp management spinlock */
	spin_lock_init(&phba->ndlp_lock);

	INIT_LIST_HEAD(&phba->port_list);
	INIT_LIST_HEAD(&phba->work_list);
	init_waitqueue_head(&phba->wait_4_mlo_m_q);

	/* Initialize the wait queue head for the kernel thread */
	init_waitqueue_head(&phba->work_waitq);

	/* Initialize the scsi buffer list used by driver for scsi IO */
	spin_lock_init(&phba->scsi_buf_list_get_lock);
	INIT_LIST_HEAD(&phba->lpfc_scsi_buf_list_get);
	spin_lock_init(&phba->scsi_buf_list_put_lock);
	INIT_LIST_HEAD(&phba->lpfc_scsi_buf_list_put);

	/* Initialize the fabric iocb list */
	INIT_LIST_HEAD(&phba->fabric_iocb_list);

	/* Initialize list to save ELS buffers */
	INIT_LIST_HEAD(&phba->elsbuf);

	/* Initialize FCF connection rec list */
	INIT_LIST_HEAD(&phba->fcf_conn_rec_list);

	return 0;
}