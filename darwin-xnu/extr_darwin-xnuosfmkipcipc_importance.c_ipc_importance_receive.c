#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_3__* task_t ;
typedef  scalar_t__ mach_voucher_attr_value_handle_t ;
typedef  int mach_msg_option_t ;
struct TYPE_14__ {unsigned int* val; } ;
struct TYPE_17__ {TYPE_1__ msgh_audit; } ;
typedef  TYPE_4__ mach_msg_max_trailer_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;
typedef  TYPE_5__* ipc_voucher_attr_recipe_t ;
typedef  int /*<<< orphan*/  ipc_voucher_attr_recipe_data_t ;
typedef  int ipc_voucher_attr_raw_recipe_array_size_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_6__* ipc_kmsg_t ;
typedef  int /*<<< orphan*/  ipc_importance_task_t ;
typedef  scalar_t__ ipc_importance_inherit_t ;
typedef  int /*<<< orphan*/  ipc_importance_elem_t ;
struct TYPE_20__ {int /*<<< orphan*/  ip_kobject; } ;
struct TYPE_19__ {scalar_t__ ikm_importance; TYPE_2__* ikm_header; TYPE_7__* ikm_voucher; } ;
struct TYPE_18__ {int content_size; scalar_t__ content; int /*<<< orphan*/  previous_voucher; int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;
struct TYPE_16__ {int /*<<< orphan*/  task_imp_base; } ;
struct TYPE_15__ {int msgh_bits; int /*<<< orphan*/  msgh_remote_port; int /*<<< orphan*/  msgh_size; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IIE_NULL ; 
 scalar_t__ III_NULL ; 
 int /*<<< orphan*/  IPC_VOUCHER_NULL ; 
 int /*<<< orphan*/  IPID_OPTION_NORMAL ; 
 scalar_t__ IP_VALID (TYPE_7__*) ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_MSGH_BITS_RAISED_IMPORTANCE (int) ; 
 int MACH_MSGH_BITS_RAISEIMP ; 
 int MACH_MSG_TYPE_MOVE_SEND ; 
 int MACH_RCV_VOUCHER ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_COPY ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_ALL ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_IMPORTANCE ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_SET_VALUE_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* convert_voucher_to_port (int /*<<< orphan*/ ) ; 
 TYPE_3__* current_task () ; 
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_control ; 
 scalar_t__ ipc_importance_inherit_from_kmsg (TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_importance_kmsg_unlink (TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_release_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_externalize_legacy_assertion (int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ ipc_importance_task_hold_internal_assertion (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipc_port_importance_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipc_port_release_send (TYPE_7__*) ; 
 scalar_t__ ipc_voucher_attr_control_create_mach_voucher (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ round_msg (int /*<<< orphan*/ ) ; 

void
ipc_importance_receive(
	ipc_kmsg_t 		kmsg,
	mach_msg_option_t	option)
{
	unsigned int sender_pid = ((mach_msg_max_trailer_t *)
				   ((vm_offset_t)kmsg->ikm_header + 
				    round_msg(kmsg->ikm_header->msgh_size)))->msgh_audit.val[5];
	task_t task_self = current_task();
	int impresult = -1;
	
	/* convert to a voucher with an inherit importance attribute? */
	if ((option & MACH_RCV_VOUCHER) != 0) {
		uint8_t recipes[2 * sizeof(ipc_voucher_attr_recipe_data_t) + 
				sizeof(mach_voucher_attr_value_handle_t)];
		ipc_voucher_attr_raw_recipe_array_size_t recipe_size = 0;
		ipc_voucher_attr_recipe_t recipe = (ipc_voucher_attr_recipe_t)recipes;
			ipc_voucher_t recv_voucher;
		mach_voucher_attr_value_handle_t handle;
		ipc_importance_inherit_t inherit;
		kern_return_t kr;

		/* set up recipe to copy the old voucher */
		if (IP_VALID(kmsg->ikm_voucher)) {
			ipc_voucher_t sent_voucher = (ipc_voucher_t)kmsg->ikm_voucher->ip_kobject;

			recipe->key = MACH_VOUCHER_ATTR_KEY_ALL;
			recipe->command = MACH_VOUCHER_ATTR_COPY;
			recipe->previous_voucher = sent_voucher;
			recipe->content_size = 0;
			recipe_size += sizeof(*recipe);
		}

		/*
		 * create an inheritance attribute from the kmsg (may be NULL)
		 * transferring any boosts from the kmsg linkage through the
		 * port directly to the new inheritance object.
		 */
		inherit = ipc_importance_inherit_from_kmsg(kmsg);
		handle = (mach_voucher_attr_value_handle_t)inherit;

		assert(IIE_NULL == kmsg->ikm_importance);

		/*
		 * Only create a new voucher if we have an inherit object
		 * (from the ikm_importance field of the incoming message), OR
		 * we have a valid incoming voucher. If we have neither of
		 * these things then there is no need to create a new voucher.
		 */
		if (IP_VALID(kmsg->ikm_voucher) || inherit != III_NULL) {
			/* replace the importance attribute with the handle we created */
			/*  our made reference on the inherit is donated to the voucher */
			recipe = (ipc_voucher_attr_recipe_t)&recipes[recipe_size];
			recipe->key = MACH_VOUCHER_ATTR_KEY_IMPORTANCE;
			recipe->command = MACH_VOUCHER_ATTR_SET_VALUE_HANDLE;
			recipe->previous_voucher = IPC_VOUCHER_NULL;
			recipe->content_size = sizeof(mach_voucher_attr_value_handle_t);
			*(mach_voucher_attr_value_handle_t *)(void *)recipe->content = handle;
			recipe_size += sizeof(*recipe) + sizeof(mach_voucher_attr_value_handle_t);

			kr = ipc_voucher_attr_control_create_mach_voucher(ipc_importance_control,
									  recipes,
									  recipe_size,
									  &recv_voucher);
			assert(KERN_SUCCESS == kr);

			/* swap the voucher port (and set voucher bits in case it didn't already exist) */
			kmsg->ikm_header->msgh_bits |= (MACH_MSG_TYPE_MOVE_SEND << 16);
			ipc_port_release_send(kmsg->ikm_voucher);
			kmsg->ikm_voucher = convert_voucher_to_port(recv_voucher);
			if (III_NULL != inherit)
				impresult = 2;
		}
	} else { /* Don't want a voucher */

		/* got linked importance? have to drop */
		if (IIE_NULL != kmsg->ikm_importance) {
			ipc_importance_elem_t elem;

			ipc_importance_lock();
			elem = ipc_importance_kmsg_unlink(kmsg);
#if IIE_REF_DEBUG
			elem->iie_kmsg_refs_dropped++;
#endif
			ipc_importance_release_locked(elem);
			/* importance unlocked */
		}

		/* With kmsg unlinked, can safely examine message importance attribute. */
		if (MACH_MSGH_BITS_RAISED_IMPORTANCE(kmsg->ikm_header->msgh_bits)) {
			ipc_importance_task_t task_imp = task_self->task_imp_base;
			ipc_port_t port = kmsg->ikm_header->msgh_remote_port;

			/* The owner of receive right might have changed, take the internal assertion */
			if (KERN_SUCCESS == ipc_importance_task_hold_internal_assertion(task_imp, 1)) {
				ipc_importance_task_externalize_legacy_assertion(task_imp, 1, sender_pid);
				impresult = 1;
			} else {
				/* The importance boost never applied to task (clear the bit) */
				kmsg->ikm_header->msgh_bits &= ~MACH_MSGH_BITS_RAISEIMP;
				impresult = 0;
			}

			/* Drop the boost on the port and the owner of the receive right */
			ip_lock(port);
			if (ipc_port_importance_delta(port, IPID_OPTION_NORMAL, -1) == FALSE) {
				ip_unlock(port);
			}
		}
	}

#if IMPORTANCE_TRACE
	if (-1 < impresult)
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_MSG, IMP_MSG_DELV)) | DBG_FUNC_NONE,
				sender_pid, task_pid(task_self),
				kmsg->ikm_header->msgh_id, impresult, 0);
	if (impresult == 2){
		/*
		 * This probe only covers new voucher-based path.  Legacy importance
		 * will trigger the probe in ipc_importance_task_externalize_assertion() 
		 * above and have impresult==1 here.
		 */
		DTRACE_BOOST5(receive_boost, task_t, task_self, int, task_pid(task_self), int, sender_pid, int, 1, int, task_self->task_imp_base->iit_assertcnt);
    }
#endif /* IMPORTANCE_TRACE */
}