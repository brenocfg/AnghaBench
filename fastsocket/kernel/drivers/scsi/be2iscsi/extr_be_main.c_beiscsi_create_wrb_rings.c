#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_14__ {void* address; } ;
struct TYPE_15__ {TYPE_5__ a64; } ;
struct TYPE_16__ {TYPE_6__ u; } ;
struct mem_array {int size; TYPE_7__ bus_address; void* virtual_address; } ;
struct iscsi_wrb {int dummy; } ;
struct hwi_wrb_context {int /*<<< orphan*/  cid; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct hwi_context_memory {TYPE_9__* be_wrbq; } ;
struct TYPE_17__ {int cxns_per_ctrl; int wrbs_per_cxn; } ;
struct beiscsi_hba {int /*<<< orphan*/  ctrl; TYPE_8__ params; struct be_mem_descriptor* init_mem; } ;
struct be_mem_descriptor {TYPE_4__* mem_array; } ;
struct be_dma_mem {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {void* address; } ;
struct TYPE_11__ {TYPE_1__ a64; } ;
struct TYPE_12__ {TYPE_2__ u; } ;
struct TYPE_13__ {int size; TYPE_3__ bus_address; void* virtual_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BE_SET_CID_TO_CRI (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWI_MEM_WRB ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int be_cmd_wrbq_create (int /*<<< orphan*/ *,struct be_dma_mem*,TYPE_9__*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwi_build_be_sgl_by_offset (struct beiscsi_hba*,struct mem_array*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  kfree (struct mem_array*) ; 
 struct mem_array* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beiscsi_create_wrb_rings(struct beiscsi_hba *phba,
			 struct hwi_context_memory *phwi_context,
			 struct hwi_controller *phwi_ctrlr)
{
	unsigned int wrb_mem_index, offset, size, num_wrb_rings;
	u64 pa_addr_lo;
	unsigned int idx, num, i;
	struct mem_array *pwrb_arr;
	void *wrb_vaddr;
	struct be_dma_mem sgl;
	struct be_mem_descriptor *mem_descr;
	struct hwi_wrb_context *pwrb_context;
	int status;

	idx = 0;
	mem_descr = phba->init_mem;
	mem_descr += HWI_MEM_WRB;
	pwrb_arr = kmalloc(sizeof(*pwrb_arr) * phba->params.cxns_per_ctrl,
			   GFP_KERNEL);
	if (!pwrb_arr) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Memory alloc failed in create wrb ring.\n");
		return -ENOMEM;
	}
	wrb_vaddr = mem_descr->mem_array[idx].virtual_address;
	pa_addr_lo = mem_descr->mem_array[idx].bus_address.u.a64.address;
	num_wrb_rings = mem_descr->mem_array[idx].size /
		(phba->params.wrbs_per_cxn * sizeof(struct iscsi_wrb));

	for (num = 0; num < phba->params.cxns_per_ctrl; num++) {
		if (num_wrb_rings) {
			pwrb_arr[num].virtual_address = wrb_vaddr;
			pwrb_arr[num].bus_address.u.a64.address	= pa_addr_lo;
			pwrb_arr[num].size = phba->params.wrbs_per_cxn *
					    sizeof(struct iscsi_wrb);
			wrb_vaddr += pwrb_arr[num].size;
			pa_addr_lo += pwrb_arr[num].size;
			num_wrb_rings--;
		} else {
			idx++;
			wrb_vaddr = mem_descr->mem_array[idx].virtual_address;
			pa_addr_lo = mem_descr->mem_array[idx].\
					bus_address.u.a64.address;
			num_wrb_rings = mem_descr->mem_array[idx].size /
					(phba->params.wrbs_per_cxn *
					sizeof(struct iscsi_wrb));
			pwrb_arr[num].virtual_address = wrb_vaddr;
			pwrb_arr[num].bus_address.u.a64.address\
						= pa_addr_lo;
			pwrb_arr[num].size = phba->params.wrbs_per_cxn *
						 sizeof(struct iscsi_wrb);
			wrb_vaddr += pwrb_arr[num].size;
			pa_addr_lo   += pwrb_arr[num].size;
			num_wrb_rings--;
		}
	}
	for (i = 0; i < phba->params.cxns_per_ctrl; i++) {
		wrb_mem_index = 0;
		offset = 0;
		size = 0;

		hwi_build_be_sgl_by_offset(phba, &pwrb_arr[i], &sgl);
		status = be_cmd_wrbq_create(&phba->ctrl, &sgl,
					    &phwi_context->be_wrbq[i]);
		if (status != 0) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : wrbq create failed.");
			kfree(pwrb_arr);
			return status;
		}
		pwrb_context = &phwi_ctrlr->wrb_context[i];
		pwrb_context->cid = phwi_context->be_wrbq[i].id;
		BE_SET_CID_TO_CRI(i, pwrb_context->cid);
	}
	kfree(pwrb_arr);
	return 0;
}