#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iscsi_endpoint {int dummy; } ;
struct TYPE_6__ {int cxns_per_ctrl; } ;
struct beiscsi_hba {int avlbl_cids; TYPE_3__ params; TYPE_2__* phwi_ctrlr; int /*<<< orphan*/ * cid_array; int /*<<< orphan*/ * ep_array; void* conn_table; } ;
struct beiscsi_conn {int dummy; } ;
struct TYPE_5__ {TYPE_1__* wrb_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hba_setup_cid_tbls(struct beiscsi_hba *phba)
{
	int i;

	phba->cid_array = kzalloc(sizeof(void *) * phba->params.cxns_per_ctrl,
				  GFP_KERNEL);
	if (!phba->cid_array) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to allocate memory in "
			    "hba_setup_cid_tbls\n");
		return -ENOMEM;
	}
	phba->ep_array = kzalloc(sizeof(struct iscsi_endpoint *) *
				 phba->params.cxns_per_ctrl, GFP_KERNEL);
	if (!phba->ep_array) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to allocate memory in "
			    "hba_setup_cid_tbls\n");
		kfree(phba->cid_array);
		phba->cid_array = NULL;
		return -ENOMEM;
	}

	phba->conn_table = kzalloc(sizeof(struct beiscsi_conn *) *
				   phba->params.cxns_per_ctrl, GFP_KERNEL);
	if (!phba->conn_table) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to allocate memory in"
			    "hba_setup_cid_tbls\n");

		kfree(phba->cid_array);
		kfree(phba->ep_array);
		phba->cid_array = NULL;
		phba->ep_array = NULL;
		return -ENOMEM;
	}

	for (i = 0; i < phba->params.cxns_per_ctrl; i++)
		phba->cid_array[i] = phba->phwi_ctrlr->wrb_context[i].cid;

	phba->avlbl_cids = phba->params.cxns_per_ctrl;
	return 0;
}