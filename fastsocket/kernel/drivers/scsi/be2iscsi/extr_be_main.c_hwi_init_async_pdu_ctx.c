#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_19__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct hwi_controller {TYPE_18__* phwi_ctxt; } ;
struct TYPE_23__ {scalar_t__ address; } ;
struct TYPE_24__ {TYPE_13__ a64; } ;
struct TYPE_25__ {TYPE_14__ u; } ;
struct TYPE_27__ {int ep_read_ptr; scalar_t__ host_write_ptr; scalar_t__ writables; int /*<<< orphan*/  free_entries; int /*<<< orphan*/  free_list; TYPE_15__ pa_base; scalar_t__ va_base; scalar_t__ handle_base; scalar_t__ ring_base; } ;
struct TYPE_31__ {scalar_t__ address; } ;
struct TYPE_32__ {TYPE_2__ a64; } ;
struct TYPE_33__ {TYPE_3__ u; } ;
struct TYPE_26__ {int ep_read_ptr; scalar_t__ host_write_ptr; scalar_t__ writables; int /*<<< orphan*/  free_entries; int /*<<< orphan*/  free_list; TYPE_4__ pa_base; scalar_t__ va_base; scalar_t__ handle_base; scalar_t__ ring_base; } ;
struct hwi_async_pdu_context {unsigned int num_entries; unsigned int buffer_size; TYPE_17__ async_data; TYPE_16__ async_header; TYPE_19__* async_entry; } ;
struct hwi_async_entry {int dummy; } ;
struct hba_parameters {unsigned int asyncpdus_per_ctrl; unsigned int defpdu_hdr_sz; unsigned int defpdu_data_sz; } ;
struct TYPE_30__ {int iscsi_cid_count; } ;
struct beiscsi_hba {struct hba_parameters params; scalar_t__ init_mem; TYPE_1__ fw_config; struct hwi_controller* phwi_ctrlr; } ;
struct be_mem_descriptor {TYPE_9__* mem_array; } ;
struct TYPE_20__ {scalar_t__ address; } ;
struct TYPE_21__ {TYPE_10__ a64; } ;
struct TYPE_22__ {TYPE_11__ u; } ;
struct async_pdu_handle {int cri; char index; int /*<<< orphan*/  link; TYPE_12__ pa; void* pbuffer; } ;
struct TYPE_35__ {scalar_t__ address; } ;
struct TYPE_36__ {TYPE_6__ a64; } ;
struct TYPE_37__ {TYPE_7__ u; } ;
struct TYPE_38__ {unsigned int size; TYPE_8__ bus_address; scalar_t__ virtual_address; } ;
struct TYPE_34__ {int /*<<< orphan*/  list; } ;
struct TYPE_29__ {int /*<<< orphan*/  data_busy_list; int /*<<< orphan*/  header_busy_list; TYPE_5__ wait_queue; } ;
struct TYPE_28__ {struct hwi_async_pdu_context* pasync_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_DATA_BUF ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_DATA_HANDLE ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_DATA_RING ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_HEADER_BUF ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_HEADER_HANDLE ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_HEADER_RING ; 
 int /*<<< orphan*/  HWI_MEM_ASYNC_PDU_CONTEXT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_19__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hwi_async_pdu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hwi_init_async_pdu_ctx(struct beiscsi_hba *phba)
{
	struct hwi_controller *phwi_ctrlr;
	struct hba_parameters *p = &phba->params;
	struct hwi_async_pdu_context *pasync_ctx;
	struct async_pdu_handle *pasync_header_h, *pasync_data_h;
	unsigned int index, idx, num_per_mem, num_async_data;
	struct be_mem_descriptor *mem_descr;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_PDU_CONTEXT;

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_ctrlr->phwi_ctxt->pasync_ctx = (struct hwi_async_pdu_context *)
				mem_descr->mem_array[0].virtual_address;
	pasync_ctx = phwi_ctrlr->phwi_ctxt->pasync_ctx;
	memset(pasync_ctx, 0, sizeof(*pasync_ctx));

	pasync_ctx->async_entry = kzalloc(sizeof(struct hwi_async_entry) *
					  phba->fw_config.iscsi_cid_count,
					  GFP_KERNEL);
	if (!pasync_ctx->async_entry) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx Mem Alloc Failed\n");
		return -ENOMEM;
	}

	pasync_ctx->num_entries = p->asyncpdus_per_ctrl;
	pasync_ctx->buffer_size = p->defpdu_hdr_sz;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_HEADER_BUF;
	if (mem_descr->mem_array[0].virtual_address) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx"
			    " HWI_MEM_ASYNC_HEADER_BUF va=%p\n",
			    mem_descr->mem_array[0].virtual_address);
	} else
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	pasync_ctx->async_header.va_base =
			mem_descr->mem_array[0].virtual_address;

	pasync_ctx->async_header.pa_base.u.a64.address =
			mem_descr->mem_array[0].bus_address.u.a64.address;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_HEADER_RING;
	if (mem_descr->mem_array[0].virtual_address) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx"
			    " HWI_MEM_ASYNC_HEADER_RING va=%p\n",
			    mem_descr->mem_array[0].virtual_address);
	} else
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	pasync_ctx->async_header.ring_base =
			mem_descr->mem_array[0].virtual_address;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_HEADER_HANDLE;
	if (mem_descr->mem_array[0].virtual_address) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx"
			    " HWI_MEM_ASYNC_HEADER_HANDLE va=%p\n",
			    mem_descr->mem_array[0].virtual_address);
	} else
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	pasync_ctx->async_header.handle_base =
			mem_descr->mem_array[0].virtual_address;
	pasync_ctx->async_header.writables = 0;
	INIT_LIST_HEAD(&pasync_ctx->async_header.free_list);


	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_DATA_RING;
	if (mem_descr->mem_array[0].virtual_address) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx"
			    " HWI_MEM_ASYNC_DATA_RING va=%p\n",
			    mem_descr->mem_array[0].virtual_address);
	} else
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	pasync_ctx->async_data.ring_base =
			mem_descr->mem_array[0].virtual_address;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_DATA_HANDLE;
	if (!mem_descr->mem_array[0].virtual_address)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	pasync_ctx->async_data.handle_base =
			mem_descr->mem_array[0].virtual_address;
	pasync_ctx->async_data.writables = 0;
	INIT_LIST_HEAD(&pasync_ctx->async_data.free_list);

	pasync_header_h =
		(struct async_pdu_handle *)pasync_ctx->async_header.handle_base;
	pasync_data_h =
		(struct async_pdu_handle *)pasync_ctx->async_data.handle_base;

	mem_descr = (struct be_mem_descriptor *)phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_DATA_BUF;
	if (mem_descr->mem_array[0].virtual_address) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : hwi_init_async_pdu_ctx"
			    " HWI_MEM_ASYNC_DATA_BUF va=%p\n",
			    mem_descr->mem_array[0].virtual_address);
	} else
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : No Virtual address\n");

	idx = 0;
	pasync_ctx->async_data.va_base =
			mem_descr->mem_array[idx].virtual_address;
	pasync_ctx->async_data.pa_base.u.a64.address =
			mem_descr->mem_array[idx].bus_address.u.a64.address;

	num_async_data = ((mem_descr->mem_array[idx].size) /
				phba->params.defpdu_data_sz);
	num_per_mem = 0;

	for (index = 0; index < p->asyncpdus_per_ctrl; index++) {
		pasync_header_h->cri = -1;
		pasync_header_h->index = (char)index;
		INIT_LIST_HEAD(&pasync_header_h->link);
		pasync_header_h->pbuffer =
			(void *)((unsigned long)
			(pasync_ctx->async_header.va_base) +
			(p->defpdu_hdr_sz * index));

		pasync_header_h->pa.u.a64.address =
			pasync_ctx->async_header.pa_base.u.a64.address +
			(p->defpdu_hdr_sz * index);

		list_add_tail(&pasync_header_h->link,
				&pasync_ctx->async_header.free_list);
		pasync_header_h++;
		pasync_ctx->async_header.free_entries++;
		pasync_ctx->async_header.writables++;

		INIT_LIST_HEAD(&pasync_ctx->async_entry[index].wait_queue.list);
		INIT_LIST_HEAD(&pasync_ctx->async_entry[index].
			       header_busy_list);
		pasync_data_h->cri = -1;
		pasync_data_h->index = (char)index;
		INIT_LIST_HEAD(&pasync_data_h->link);

		if (!num_async_data) {
			num_per_mem = 0;
			idx++;
			pasync_ctx->async_data.va_base =
				mem_descr->mem_array[idx].virtual_address;
			pasync_ctx->async_data.pa_base.u.a64.address =
				mem_descr->mem_array[idx].
				bus_address.u.a64.address;

			num_async_data = ((mem_descr->mem_array[idx].size) /
					phba->params.defpdu_data_sz);
		}
		pasync_data_h->pbuffer =
			(void *)((unsigned long)
			(pasync_ctx->async_data.va_base) +
			(p->defpdu_data_sz * num_per_mem));

		pasync_data_h->pa.u.a64.address =
		    pasync_ctx->async_data.pa_base.u.a64.address +
		    (p->defpdu_data_sz * num_per_mem);
		num_per_mem++;
		num_async_data--;

		list_add_tail(&pasync_data_h->link,
			      &pasync_ctx->async_data.free_list);
		pasync_data_h++;
		pasync_ctx->async_data.free_entries++;
		pasync_ctx->async_data.writables++;

		INIT_LIST_HEAD(&pasync_ctx->async_entry[index].data_busy_list);
	}

	pasync_ctx->async_header.host_write_ptr = 0;
	pasync_ctx->async_header.ep_read_ptr = -1;
	pasync_ctx->async_data.host_write_ptr = 0;
	pasync_ctx->async_data.ep_read_ptr = -1;

	return 0;
}