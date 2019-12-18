#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int cfg_devloss_tmo; struct lpfc_hba* phba; } ;
struct TYPE_2__ {size_t fcp_ring; int /*<<< orphan*/ * ring; } ;
struct lpfc_hba {TYPE_1__ sli; } ;
typedef  int /*<<< orphan*/  lpfc_ctx_cmd ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LPFC_CTX_HOST ; 
 int /*<<< orphan*/  LPFC_CTX_LUN ; 
 int /*<<< orphan*/  LPFC_CTX_TGT ; 
 int SUCCESS ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli_abort_iocb (struct lpfc_vport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_sli_sum_iocb (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int
lpfc_reset_flush_io_context(struct lpfc_vport *vport, uint16_t tgt_id,
			uint64_t lun_id, lpfc_ctx_cmd context)
{
	struct lpfc_hba   *phba = vport->phba;
	unsigned long later;
	int cnt;

	cnt = lpfc_sli_sum_iocb(vport, tgt_id, lun_id, context);
	if (cnt)
		lpfc_sli_abort_iocb(vport, &phba->sli.ring[phba->sli.fcp_ring],
				    tgt_id, lun_id, context);
	later = msecs_to_jiffies(2 * vport->cfg_devloss_tmo * 1000) + jiffies;
	while (time_after(later, jiffies) && cnt) {
		schedule_timeout_uninterruptible(msecs_to_jiffies(20));
		cnt = lpfc_sli_sum_iocb(vport, tgt_id, lun_id, context);
	}
	if (cnt) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_FCP,
			"0724 I/O flush failure for context %s : cnt x%x\n",
			((context == LPFC_CTX_LUN) ? "LUN" :
			 ((context == LPFC_CTX_TGT) ? "TGT" :
			  ((context == LPFC_CTX_HOST) ? "HOST" : "Unknown"))),
			cnt);
		return FAILED;
	}
	return SUCCESS;
}