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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_iocbq {int dummy; } ;
struct lpfc_hba {int (* __lpfc_sli_issue_iocb ) (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 

int
__lpfc_sli_issue_iocb(struct lpfc_hba *phba, uint32_t ring_number,
		struct lpfc_iocbq *piocb, uint32_t flag)
{
	return phba->__lpfc_sli_issue_iocb(phba, ring_number, piocb, flag);
}