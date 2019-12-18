#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  mach_msg_timeout_t ;
typedef  int mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  int /*<<< orphan*/  mach_msg_priority_t ;
typedef  int /*<<< orphan*/  mach_msg_option_t ;
struct TYPE_17__ {int /*<<< orphan*/  msgh_trailer_size; int /*<<< orphan*/  msgh_trailer_type; int /*<<< orphan*/  msgh_audit; int /*<<< orphan*/  msgh_sender; } ;
typedef  TYPE_3__ mach_msg_max_trailer_t ;
struct TYPE_18__ {int msgh_bits; } ;
typedef  TYPE_4__ mach_msg_header_t ;
typedef  int /*<<< orphan*/  mach_msg_base_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_5__* ipc_kmsg_t ;
struct TYPE_19__ {TYPE_2__* ikm_header; } ;
struct TYPE_16__ {int msgh_size; } ;
struct TYPE_15__ {int /*<<< orphan*/  audit_token; int /*<<< orphan*/  sec_token; } ;
struct TYPE_14__ {TYPE_1__* task; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 TYPE_5__* IKM_NULL ; 
 int /*<<< orphan*/  KDBG (int,...) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_IPC_KMSG_INFO ; 
 int /*<<< orphan*/  MACH_IPC_KMSG_LINK ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 int /*<<< orphan*/  MACH_MSG_BODY_NULL ; 
 int MACH_MSG_SIZE_MAX ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_FORMAT_0 ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_MINIMUM_SIZE ; 
 int /*<<< orphan*/  MACH_SEND_KERNEL ; 
 int /*<<< orphan*/  MACH_SEND_MSG_TOO_SMALL ; 
 int /*<<< orphan*/  MACH_SEND_NO_BUFFER ; 
 int /*<<< orphan*/  MACH_SEND_TOO_LARGE ; 
 int MAX_TRAILER_SIZE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (uintptr_t) ; 
 int /*<<< orphan*/  current_map () ; 
 int /*<<< orphan*/  current_space () ; 
 TYPE_12__* current_thread () ; 
 TYPE_5__* ipc_kmsg_alloc (int) ; 
 int /*<<< orphan*/  ipc_kmsg_copyin (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kmsg_copyout_pseudo (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ipc_kmsg_send (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

mach_msg_return_t
mach_msg_send(
	mach_msg_header_t	*msg,
	mach_msg_option_t	option,
	mach_msg_size_t		send_size,
	mach_msg_timeout_t	send_timeout,
	mach_msg_priority_t	override)
{
	ipc_space_t space = current_space();
	vm_map_t map = current_map();
	ipc_kmsg_t kmsg;
	mach_msg_return_t mr;
	mach_msg_size_t	msg_and_trailer_size;
	mach_msg_max_trailer_t	*trailer;

	option |= MACH_SEND_KERNEL;

	if ((send_size & 3) ||
	    send_size < sizeof(mach_msg_header_t) ||
	    (send_size < sizeof(mach_msg_base_t) && (msg->msgh_bits & MACH_MSGH_BITS_COMPLEX)))
		return MACH_SEND_MSG_TOO_SMALL;

	if (send_size > MACH_MSG_SIZE_MAX - MAX_TRAILER_SIZE)
		return MACH_SEND_TOO_LARGE;
	
	KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_START);

	msg_and_trailer_size = send_size + MAX_TRAILER_SIZE;

	kmsg = ipc_kmsg_alloc(msg_and_trailer_size);

	if (kmsg == IKM_NULL) {
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, MACH_SEND_NO_BUFFER);
		return MACH_SEND_NO_BUFFER;
	}

	KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_LINK) | DBG_FUNC_NONE,
			      (uintptr_t)0, /* this should only be called from the kernel! */
			      VM_KERNEL_ADDRPERM((uintptr_t)kmsg),
			      0, 0,
			      0);
	(void) memcpy((void *) kmsg->ikm_header, (const void *) msg, send_size);

	kmsg->ikm_header->msgh_size = send_size;

	/* 
	 * reserve for the trailer the largest space (MAX_TRAILER_SIZE)
	 * However, the internal size field of the trailer (msgh_trailer_size)
	 * is initialized to the minimum (sizeof(mach_msg_trailer_t)), to optimize
	 * the cases where no implicit data is requested.
	 */
	trailer = (mach_msg_max_trailer_t *) ((vm_offset_t)kmsg->ikm_header + send_size);
	trailer->msgh_sender = current_thread()->task->sec_token;
	trailer->msgh_audit = current_thread()->task->audit_token;
	trailer->msgh_trailer_type = MACH_MSG_TRAILER_FORMAT_0;
	trailer->msgh_trailer_size = MACH_MSG_TRAILER_MINIMUM_SIZE;

	mr = ipc_kmsg_copyin(kmsg, space, map, override, &option);

	if (mr != MACH_MSG_SUCCESS) {
		ipc_kmsg_free(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, mr);
		return mr;
	}

	mr = ipc_kmsg_send(kmsg, option, send_timeout);

	if (mr != MACH_MSG_SUCCESS) {
	    mr |= ipc_kmsg_copyout_pseudo(kmsg, space, map, MACH_MSG_BODY_NULL);
	    (void) memcpy((void *) msg, (const void *) kmsg->ikm_header, 
			  kmsg->ikm_header->msgh_size);
	    ipc_kmsg_free(kmsg);
	    KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, mr);
	}

	return mr;
}