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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_qla_host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_semaphore (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ql4xxx_sem_unlock(struct scsi_qla_host * ha, u32 sem_mask)
{
	unsigned long flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	writel(sem_mask, isp_semaphore(ha));
	readl(isp_semaphore(ha));
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	DEBUG2(printk("scsi%ld : UNLOCK SEM - mask= 0x%x\n", ha->host_no,
		      sem_mask));
}