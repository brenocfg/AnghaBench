#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  mach_msg_timeout_t ;
typedef  int mach_msg_return_t ;
typedef  int /*<<< orphan*/  mach_msg_option_t ;
typedef  TYPE_3__* ipc_port_t ;
typedef  TYPE_4__* ipc_kmsg_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_28__ {int /*<<< orphan*/  imq_seqno; } ;
struct TYPE_27__ {TYPE_1__* ikm_header; } ;
struct TYPE_26__ {scalar_t__ ip_receiver; TYPE_7__ ip_messages; } ;
struct TYPE_25__ {int options; } ;
struct TYPE_24__ {int /*<<< orphan*/  messages_sent; } ;
struct TYPE_23__ {int msgh_bits; void* msgh_remote_port; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 scalar_t__ FALSE ; 
 TYPE_4__* IKM_NULL ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  KDBG (int,...) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_IPC_KMSG_INFO ; 
 int MACH_MSGH_BITS_CIRCULAR ; 
 int MACH_MSG_SUCCESS ; 
 void* MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_SEND_ALWAYS ; 
 int MACH_SEND_INVALID_DEST ; 
 int /*<<< orphan*/  MACH_SEND_TIMEOUT ; 
 int TH_OPT_HONOR_QLIMIT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_20__* current_task () ; 
 TYPE_2__* current_thread () ; 
 scalar_t__ did_importance ; 
 int /*<<< orphan*/  imq_lock (TYPE_7__*) ; 
 int /*<<< orphan*/  ip_active (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_importance_clean (TYPE_4__*) ; 
 int /*<<< orphan*/  ipc_kmsg_destroy (TYPE_4__*) ; 
 TYPE_4__* ipc_kobject_server (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ipc_mqueue_send (TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_space_kernel ; 
 int /*<<< orphan*/  ipc_voucher_send_preprocessing (TYPE_4__*) ; 
 int /*<<< orphan*/  set_ip_srp_msg_sent (TYPE_3__*) ; 

mach_msg_return_t
ipc_kmsg_send(
	ipc_kmsg_t		kmsg,
	mach_msg_option_t	option,
	mach_msg_timeout_t	send_timeout)
{
	ipc_port_t port;
	thread_t th = current_thread();
	mach_msg_return_t error = MACH_MSG_SUCCESS;
	boolean_t kernel_reply = FALSE;

	/* Check if honor qlimit flag is set on thread. */
	if ((th->options & TH_OPT_HONOR_QLIMIT) == TH_OPT_HONOR_QLIMIT) {
		/* Remove the MACH_SEND_ALWAYS flag to honor queue limit. */
		option &= (~MACH_SEND_ALWAYS);
		/* Add the timeout flag since the message queue might be full. */
		option |= MACH_SEND_TIMEOUT;
		th->options &= (~TH_OPT_HONOR_QLIMIT);
	}

#if IMPORTANCE_INHERITANCE
	bool did_importance = false;
#if IMPORTANCE_TRACE
	mach_msg_id_t imp_msgh_id = -1;
	int           sender_pid  = -1;
#endif /* IMPORTANCE_TRACE */
#endif /* IMPORTANCE_INHERITANCE */

	/* don't allow the creation of a circular loop */
	if (kmsg->ikm_header->msgh_bits & MACH_MSGH_BITS_CIRCULAR) {
		ipc_kmsg_destroy(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, MACH_MSGH_BITS_CIRCULAR);
		return MACH_MSG_SUCCESS;
	}

	ipc_voucher_send_preprocessing(kmsg);

	port = (ipc_port_t) kmsg->ikm_header->msgh_remote_port;
	assert(IP_VALID(port));
	ip_lock(port);

#if IMPORTANCE_INHERITANCE
retry:
#endif /* IMPORTANCE_INHERITANCE */
	/*
	 *	Can't deliver to a dead port.
	 *	However, we can pretend it got sent
	 *	and was then immediately destroyed.
	 */
	if (!ip_active(port)) {
		ip_unlock(port);
#if MACH_FLIPC
        if (MACH_NODE_VALID(kmsg->ikm_node) && FPORT_VALID(port->ip_messages.imq_fport))
            flipc_msg_ack(kmsg->ikm_node, &port->ip_messages, FALSE);
#endif
		if (did_importance) {
			/*
			 * We're going to pretend we delivered this message
			 * successfully, and just eat the kmsg. However, the
			 * kmsg is actually visible via the importance_task!
			 * We need to cleanup this linkage before we destroy
			 * the message, and more importantly before we set the
			 * msgh_remote_port to NULL. See: 34302571
			 */
			ipc_importance_clean(kmsg);
		}
		ip_release(port);  /* JMM - Future: release right, not just ref */
		kmsg->ikm_header->msgh_remote_port = MACH_PORT_NULL;
		ipc_kmsg_destroy(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, MACH_SEND_INVALID_DEST);
		return MACH_MSG_SUCCESS;
	}

	if (port->ip_receiver == ipc_space_kernel) {

		/*
		 *	We can check ip_receiver == ipc_space_kernel
		 *	before checking that the port is active because
		 *	ipc_port_dealloc_kernel clears ip_receiver
		 *	before destroying a kernel port.
		 */
		assert(ip_active(port));
		port->ip_messages.imq_seqno++;
		ip_unlock(port);

		current_task()->messages_sent++;

		/*
		 * Call the server routine, and get the reply message to send.
		 */
		kmsg = ipc_kobject_server(kmsg, option);
		if (kmsg == IKM_NULL)
			return MACH_MSG_SUCCESS;

		/* restart the KMSG_INFO tracing for the reply message */
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_START);
		port = (ipc_port_t) kmsg->ikm_header->msgh_remote_port;
		assert(IP_VALID(port));
		ip_lock(port);
		/* fall thru with reply - same options */
		kernel_reply = TRUE;
		if (!ip_active(port))
			error = MACH_SEND_INVALID_DEST;
	}

#if IMPORTANCE_INHERITANCE
	/*
	 * Need to see if this message needs importance donation and/or
	 * propagation.  That routine can drop the port lock temporarily.
	 * If it does we'll have to revalidate the destination.
	 */
	if (!did_importance) {
		did_importance = true;
		if (ipc_importance_send(kmsg, option))
	  		goto retry;
	}
#endif /* IMPORTANCE_INHERITANCE */

	if (error != MACH_MSG_SUCCESS) {
		ip_unlock(port);
	} else {
		/*
		 * We have a valid message and a valid reference on the port.
		 * we can unlock the port and call mqueue_send() on its message
		 * queue. Lock message queue while port is locked.
		 */
		imq_lock(&port->ip_messages);

		set_ip_srp_msg_sent(port);

		ip_unlock(port);

		error = ipc_mqueue_send(&port->ip_messages, kmsg, option,
				send_timeout);
	}

#if IMPORTANCE_INHERITANCE
	if (did_importance) {
		__unused int importance_cleared = 0;
		switch (error) {
			case MACH_SEND_TIMED_OUT:
			case MACH_SEND_NO_BUFFER:
			case MACH_SEND_INTERRUPTED:
			case MACH_SEND_INVALID_DEST:
				/*
				 * We still have the kmsg and its
				 * reference on the port.  But we
				 * have to back out the importance
				 * boost.
				 *
				 * The port could have changed hands,
				 * be inflight to another destination,
				 * etc...  But in those cases our
				 * back-out will find the new owner
				 * (and all the operations that
				 * transferred the right should have
				 * applied their own boost adjustments
				 * to the old owner(s)).
				 */
				importance_cleared = 1;
				ipc_importance_clean(kmsg);
				break;

			case MACH_MSG_SUCCESS:
			default:
				break;
		}
#if IMPORTANCE_TRACE
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_MSG, IMP_MSG_SEND)) | DBG_FUNC_END,
		                          task_pid(current_task()), sender_pid, imp_msgh_id, importance_cleared, 0);
#endif /* IMPORTANCE_TRACE */
	}
#endif /* IMPORTANCE_INHERITANCE */

	/*
	 * If the port has been destroyed while we wait, treat the message
	 * as a successful delivery (like we do for an inactive port).
	 */
	if (error == MACH_SEND_INVALID_DEST) {
#if MACH_FLIPC
        if (MACH_NODE_VALID(kmsg->ikm_node) && FPORT_VALID(port->ip_messages.imq_fport))
            flipc_msg_ack(kmsg->ikm_node, &port->ip_messages, FALSE);
#endif
		ip_release(port); /* JMM - Future: release right, not just ref */
		kmsg->ikm_header->msgh_remote_port = MACH_PORT_NULL;
		ipc_kmsg_destroy(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, MACH_SEND_INVALID_DEST);
		return MACH_MSG_SUCCESS;
	}

	if (error != MACH_MSG_SUCCESS && kernel_reply) {
		/*
		 * Kernel reply messages that fail can't be allowed to
		 * pseudo-receive on error conditions. We need to just treat
		 * the message as a successful delivery.
		 */
#if MACH_FLIPC
        if (MACH_NODE_VALID(kmsg->ikm_node) && FPORT_VALID(port->ip_messages.imq_fport))
            flipc_msg_ack(kmsg->ikm_node, &port->ip_messages, FALSE);
#endif
		ip_release(port); /* JMM - Future: release right, not just ref */
		kmsg->ikm_header->msgh_remote_port = MACH_PORT_NULL;
		ipc_kmsg_destroy(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, error);
		return MACH_MSG_SUCCESS;
	}
	return error;
}