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
struct sgl_handle {int dummy; } ;
struct TYPE_2__ {int icds_per_ctrl; int ios_per_ctrl; } ;
struct beiscsi_hba {size_t eh_sgl_free_index; TYPE_1__ params; int /*<<< orphan*/  eh_sgl_hndl_avbl; struct sgl_handle** eh_sgl_hndl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

void
free_mgmt_sgl_handle(struct beiscsi_hba *phba, struct sgl_handle *psgl_handle)
{

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BM_%d : In  free_mgmt_sgl_handle,"
		    "eh_sgl_free_index=%d\n",
		    phba->eh_sgl_free_index);

	if (phba->eh_sgl_hndl_base[phba->eh_sgl_free_index]) {
		/*
		 * this can happen if clean_task is called on a task that
		 * failed in xmit_task or alloc_pdu.
		 */
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BM_%d : Double Free in eh SGL ,"
			    "eh_sgl_free_index=%d\n",
			    phba->eh_sgl_free_index);
		return;
	}
	phba->eh_sgl_hndl_base[phba->eh_sgl_free_index] = psgl_handle;
	phba->eh_sgl_hndl_avbl++;
	if (phba->eh_sgl_free_index ==
	    (phba->params.icds_per_ctrl - phba->params.ios_per_ctrl - 1))
		phba->eh_sgl_free_index = 0;
	else
		phba->eh_sgl_free_index++;
}