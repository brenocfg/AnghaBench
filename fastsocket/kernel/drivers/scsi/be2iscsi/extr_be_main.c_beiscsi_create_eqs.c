#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hwi_context_memory {TYPE_2__* be_eq; int /*<<< orphan*/  cur_eqd; } ;
struct TYPE_3__ {int num_eq_entries; } ;
struct beiscsi_hba {int num_cpus; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  ctrl; TYPE_1__ params; scalar_t__ msix_enabled; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; void* va; } ;
struct be_queue_info {struct be_dma_mem dma_mem; int /*<<< orphan*/  id; } ;
struct be_eq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {struct be_queue_info q; struct beiscsi_hba* phba; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned int PAGES_REQUIRED (int) ; 
 unsigned int PAGE_SIZE ; 
 int be_fill_queue (struct be_queue_info*,int,int,void*) ; 
 int beiscsi_cmd_eq_create (int /*<<< orphan*/ *,struct be_queue_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_create_eqs(struct beiscsi_hba *phba,
			     struct hwi_context_memory *phwi_context)
{
	unsigned int i, num_eq_pages;
	int ret = 0, eq_for_mcc;
	struct be_queue_info *eq;
	struct be_dma_mem *mem;
	void *eq_vaddress;
	dma_addr_t paddr;

	num_eq_pages = PAGES_REQUIRED(phba->params.num_eq_entries * \
				      sizeof(struct be_eq_entry));

	if (phba->msix_enabled)
		eq_for_mcc = 1;
	else
		eq_for_mcc = 0;
	for (i = 0; i < (phba->num_cpus + eq_for_mcc); i++) {
		eq = &phwi_context->be_eq[i].q;
		mem = &eq->dma_mem;
		phwi_context->be_eq[i].phba = phba;
		eq_vaddress = pci_alloc_consistent(phba->pcidev,
						     num_eq_pages * PAGE_SIZE,
						     &paddr);
		if (!eq_vaddress)
			goto create_eq_error;

		mem->va = eq_vaddress;
		ret = be_fill_queue(eq, phba->params.num_eq_entries,
				    sizeof(struct be_eq_entry), eq_vaddress);
		if (ret) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : be_fill_queue Failed for EQ\n");
			goto create_eq_error;
		}

		mem->dma = paddr;
		ret = beiscsi_cmd_eq_create(&phba->ctrl, eq,
					    phwi_context->cur_eqd);
		if (ret) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : beiscsi_cmd_eq_create"
				    "Failed for EQ\n");
			goto create_eq_error;
		}

		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : eqid = %d\n",
			    phwi_context->be_eq[i].q.id);
	}
	return 0;
create_eq_error:
	for (i = 0; i < (phba->num_cpus + eq_for_mcc); i++) {
		eq = &phwi_context->be_eq[i].q;
		mem = &eq->dma_mem;
		if (mem->va)
			pci_free_consistent(phba->pcidev, num_eq_pages
					    * PAGE_SIZE,
					    mem->va, mem->dma);
	}
	return ret;
}