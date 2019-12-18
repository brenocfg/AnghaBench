#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct rpc_request_hdr {int /*<<< orphan*/  xid; } ;
struct adsp_rtos_mp_mtoa_init_info_type {size_t image_count; size_t num_queue_offsets; size_t** queue_offsets; size_t num_task_module_entries; size_t** task_to_module_tbl; size_t module_table_size; size_t* module_entries; struct queue_to_offset_type** queue_offsets_tbl; } ;
struct adsp_rtos_mp_mtoa_type {size_t module; size_t image; } ;
struct TYPE_9__ {struct adsp_rtos_mp_mtoa_init_info_type mp_mtoa_init_packet; struct adsp_rtos_mp_mtoa_type mp_mtoa_packet; } ;
struct TYPE_8__ {size_t event; size_t proc_id; } ;
struct TYPE_10__ {size_t desc_field; TYPE_3__ adsp_rtos_mp_mtoa_data; TYPE_2__ mp_mtoa_header; } ;
struct rpc_adsp_rtos_modem_to_app_args_t {size_t event; size_t proc_id; size_t module; size_t image; TYPE_4__ mtoa_pkt; } ;
struct queue_to_offset_type {size_t offset; size_t queue; } ;
struct msm_adsp_module {size_t name; int /*<<< orphan*/  driver_data; TYPE_1__* ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  state_wait; void* state; int /*<<< orphan*/  info; } ;
typedef  size_t int32_t ;
struct TYPE_11__ {int /*<<< orphan*/  init_info_wait; int /*<<< orphan*/  init_info_state; struct adsp_rtos_mp_mtoa_init_info_type* init_info_ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* event ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* ADSP_STATE_DISABLED ; 
 void* ADSP_STATE_ENABLED ; 
 int /*<<< orphan*/  ADSP_STATE_INIT_INFO ; 
 int /*<<< orphan*/  EVENT_LEN ; 
 int /*<<< orphan*/  EVENT_MSG_ID ; 
 int /*<<< orphan*/  RPC_ACCEPTSTAT_GARBAGE_ARGS ; 
 int /*<<< orphan*/  RPC_ACCEPTSTAT_SUCCESS ; 
#define  RPC_ADSP_RTOS_CMD_FAIL 133 
#define  RPC_ADSP_RTOS_CMD_SUCCESS 132 
#define  RPC_ADSP_RTOS_DISABLE_FAIL 131 
 scalar_t__ RPC_ADSP_RTOS_INIT_INFO ; 
#define  RPC_ADSP_RTOS_MOD_DISABLE 130 
#define  RPC_ADSP_RTOS_MOD_READY 129 
#define  RPC_ADSP_RTOS_SERVICE_RESET 128 
 TYPE_5__ adsp_info ; 
 int /*<<< orphan*/  adsp_set_image (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ be32_to_cpu (size_t) ; 
 struct msm_adsp_module* find_adsp_module_by_id (TYPE_5__*,size_t) ; 
 size_t* modem_event_addr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  read_modem_event ; 
 int /*<<< orphan*/  rpc_cb_server_client ; 
 int /*<<< orphan*/  rpc_send_accepted_void_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_adsp_rtos_mtoa_app(struct rpc_request_hdr *req)
{
	struct rpc_adsp_rtos_modem_to_app_args_t *args =
		(struct rpc_adsp_rtos_modem_to_app_args_t *)req;
	uint32_t event;
	uint32_t proc_id;
	uint32_t module_id;
	uint32_t image;
	struct msm_adsp_module *module;
#if CONFIG_MSM_AMSS_VERSION >= 6350
	struct adsp_rtos_mp_mtoa_type *pkt_ptr =
		&args->mtoa_pkt.adsp_rtos_mp_mtoa_data.mp_mtoa_packet;

	event = be32_to_cpu(args->mtoa_pkt.mp_mtoa_header.event);
	proc_id = be32_to_cpu(args->mtoa_pkt.mp_mtoa_header.proc_id);
	module_id = be32_to_cpu(pkt_ptr->module);
	image = be32_to_cpu(pkt_ptr->image);

	if (be32_to_cpu(args->mtoa_pkt.desc_field) == RPC_ADSP_RTOS_INIT_INFO) {
		struct queue_to_offset_type *qptr;
		struct queue_to_offset_type *qtbl;
		uint32_t *mptr;
		uint32_t *mtbl;
		uint32_t q_idx;
		uint32_t num_entries;
		uint32_t entries_per_image;
		struct adsp_rtos_mp_mtoa_init_info_type *iptr;
		struct adsp_rtos_mp_mtoa_init_info_type *sptr;
		int32_t i_no, e_idx;

		pr_info("adsp:INIT_INFO Event\n");
		sptr = &args->mtoa_pkt.adsp_rtos_mp_mtoa_data.
				mp_mtoa_init_packet;

		iptr = adsp_info.init_info_ptr;
		iptr->image_count = be32_to_cpu(sptr->image_count);
		iptr->num_queue_offsets = be32_to_cpu(sptr->num_queue_offsets);
		num_entries = iptr->num_queue_offsets;
		qptr = &sptr->queue_offsets_tbl[0][0];
		for (i_no = 0; i_no < iptr->image_count; i_no++) {
			qtbl = &iptr->queue_offsets_tbl[i_no][0];
			for (e_idx = 0; e_idx < num_entries; e_idx++) {
				qtbl[e_idx].offset = be32_to_cpu(qptr->offset);
				qtbl[e_idx].queue = be32_to_cpu(qptr->queue);
				q_idx = be32_to_cpu(qptr->queue);
				iptr->queue_offsets[i_no][q_idx] =
						qtbl[e_idx].offset;
				qptr++;
			}
		}

		num_entries = be32_to_cpu(sptr->num_task_module_entries);
		iptr->num_task_module_entries = num_entries;
		entries_per_image = num_entries / iptr->image_count;
		mptr = &sptr->task_to_module_tbl[0][0];
		for (i_no = 0; i_no < iptr->image_count; i_no++) {
			mtbl = &iptr->task_to_module_tbl[i_no][0];
			for (e_idx = 0; e_idx < entries_per_image; e_idx++) {
				mtbl[e_idx] = be32_to_cpu(*mptr);
				mptr++;
			}
		}

		iptr->module_table_size = be32_to_cpu(sptr->module_table_size);
		mptr = &sptr->module_entries[0];
		for (i_no = 0; i_no < iptr->module_table_size; i_no++)
			iptr->module_entries[i_no] = be32_to_cpu(mptr[i_no]);
		adsp_info.init_info_state = ADSP_STATE_INIT_INFO;
		rpc_send_accepted_void_reply(rpc_cb_server_client, req->xid,
						RPC_ACCEPTSTAT_SUCCESS);
		wake_up(&adsp_info.init_info_wait);

		return;
	}
#else
	event = be32_to_cpu(args->event);
	proc_id = be32_to_cpu(args->proc_id);
	module_id = be32_to_cpu(args->module);
	image = be32_to_cpu(args->image);
#endif

	pr_info("adsp: rpc event=%d, proc_id=%d, module=%d, image=%d\n",
		event, proc_id, module_id, image);

	module = find_adsp_module_by_id(&adsp_info, module_id);
	if (!module) {
		pr_err("adsp: module %d is not supported!\n", module_id);
		rpc_send_accepted_void_reply(rpc_cb_server_client, req->xid,
				RPC_ACCEPTSTAT_GARBAGE_ARGS);
		return;
	}

	mutex_lock(&module->lock);
	switch (event) {
	case RPC_ADSP_RTOS_MOD_READY:
		pr_info("adsp: module %s: READY\n", module->name);
		module->state = ADSP_STATE_ENABLED;
		wake_up(&module->state_wait);
		adsp_set_image(module->info, image);
		break;
	case RPC_ADSP_RTOS_MOD_DISABLE:
		pr_info("adsp: module %s: DISABLED\n", module->name);
		module->state = ADSP_STATE_DISABLED;
		wake_up(&module->state_wait);
		break;
	case RPC_ADSP_RTOS_SERVICE_RESET:
		pr_info("adsp: module %s: SERVICE_RESET\n", module->name);
		module->state = ADSP_STATE_DISABLED;
		wake_up(&module->state_wait);
		break;
	case RPC_ADSP_RTOS_CMD_SUCCESS:
		pr_info("adsp: module %s: CMD_SUCCESS\n", module->name);
		break;
	case RPC_ADSP_RTOS_CMD_FAIL:
		pr_info("adsp: module %s: CMD_FAIL\n", module->name);
		break;
#if CONFIG_MSM_AMSS_VERSION >= 6350
	case RPC_ADSP_RTOS_DISABLE_FAIL:
		pr_info("adsp: module %s: DISABLE_FAIL\n", module->name);
		break;
#endif
	default:
		pr_info("adsp: unknown event %d\n", event);
		rpc_send_accepted_void_reply(rpc_cb_server_client, req->xid,
					     RPC_ACCEPTSTAT_GARBAGE_ARGS);
		mutex_unlock(&module->lock);
		return;
	}
	rpc_send_accepted_void_reply(rpc_cb_server_client, req->xid,
				     RPC_ACCEPTSTAT_SUCCESS);
	mutex_unlock(&module->lock);
#ifdef CONFIG_MSM_ADSP_REPORT_EVENTS
	modem_event_addr = (uint32_t *)req;
	module->ops->event(module->driver_data, EVENT_MSG_ID,
				EVENT_LEN, read_modem_event);
#endif
}