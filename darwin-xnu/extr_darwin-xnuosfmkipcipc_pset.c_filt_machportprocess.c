#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wait_result_t ;
typedef  int uint64_t ;
typedef  TYPE_2__* thread_t ;
struct kevent_internal_s {int* ext; int flags; scalar_t__ fflags; void* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_mqueue; } ;
struct knote {int kn_sfflags; scalar_t__* kn_ext; struct kevent_internal_s kn_kevent; TYPE_1__ kn_ptr; } ;
struct filt_process_s {int fp_data_out; scalar_t__ fp_data_resid; int fp_flags; } ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ mach_msg_size_t ;
typedef  int mach_msg_option_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  int /*<<< orphan*/  ipc_mqueue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int ith_msize; int ith_option; scalar_t__ ith_state; scalar_t__ turnstile; scalar_t__ ith_kmsg; scalar_t__ ith_qos_override; scalar_t__ ith_qos; void* ith_receiver_name; struct knote* ith_knote; int /*<<< orphan*/ * ith_continuation; scalar_t__ ith_rsize; scalar_t__ ith_msg_addr; int /*<<< orphan*/  ith_object; } ;

/* Variables and functions */
 int EV_EOF ; 
 scalar_t__ FALSE ; 
 int FILTER_ACTIVE ; 
 int FILTER_RESET_EVENT_QOS ; 
 scalar_t__ IKM_NULL ; 
 int KEVENT_FLAG_STACK_DATA ; 
 scalar_t__ MACH_MSG_SUCCESS ; 
 void* MACH_PORT_NULL ; 
 scalar_t__ MACH_RCV_IN_PROGRESS ; 
 int MACH_RCV_LARGE ; 
 int MACH_RCV_LARGE_IDENTITY ; 
 int MACH_RCV_MSG ; 
 int MACH_RCV_STACK ; 
 scalar_t__ MACH_RCV_TIMED_OUT ; 
 int MACH_RCV_TIMEOUT ; 
 scalar_t__ MACH_RCV_TOO_LARGE ; 
 int MACH_RCV_TRAILER_MASK ; 
 int MACH_RCV_VOUCHER ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ THREAD_NOT_WAITING ; 
 scalar_t__ THREAD_RESTART ; 
 scalar_t__ TRUE ; 
 scalar_t__ TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_release (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_mqueue_receive_on_thread (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mach_msg_receive_results (scalar_t__*) ; 
 int /*<<< orphan*/  mqueue_to_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_machportprocess(
	struct knote *kn,
	struct filt_process_s *process_data,
	struct kevent_internal_s *kev)
{
	ipc_mqueue_t mqueue = kn->kn_ptr.p_mqueue;
	ipc_object_t object = mqueue_to_object(mqueue);
	thread_t self = current_thread();
	boolean_t used_filtprocess_data = FALSE;

	wait_result_t wresult;
	mach_msg_option_t option;
	mach_vm_address_t addr;
	mach_msg_size_t	size;

	/* Capture current state */
	*kev = kn->kn_kevent;
	kev->ext[3] = 0; /* hide our port reference from userspace */

	/* If already deallocated/moved return one last EOF event */
	if (kev->flags & EV_EOF) {
		return FILTER_ACTIVE | FILTER_RESET_EVENT_QOS;
	}

	/*
	 * Only honor supported receive options. If no options are
	 * provided, just force a MACH_RCV_TOO_LARGE to detect the
	 * name of the port and sizeof the waiting message.
	 */
	option = kn->kn_sfflags & (MACH_RCV_MSG|MACH_RCV_LARGE|MACH_RCV_LARGE_IDENTITY|
	                           MACH_RCV_TRAILER_MASK|MACH_RCV_VOUCHER);

	if (option & MACH_RCV_MSG) {
		addr = (mach_vm_address_t) kn->kn_ext[0];
		size = (mach_msg_size_t) kn->kn_ext[1];

		/*
		 * If the kevent didn't specify a buffer and length, carve a buffer
		 * from the filter processing data according to the flags.
		 */
		if (size == 0 && process_data != NULL) {
			used_filtprocess_data = TRUE;

			addr = (mach_vm_address_t)process_data->fp_data_out;
			size = (mach_msg_size_t)process_data->fp_data_resid;
			option |= (MACH_RCV_LARGE | MACH_RCV_LARGE_IDENTITY);
			if (process_data->fp_flags & KEVENT_FLAG_STACK_DATA)
				option |= MACH_RCV_STACK;
		}
	} else {
		/* just detect the port name (if a set) and size of the first message */
		option = MACH_RCV_LARGE;
		addr = 0;
		size = 0;
	}

	imq_lock(mqueue);

	/* just use the reference from here on out */
	io_reference(object);

	/*
	 * Set up to receive a message or the notification of a
	 * too large message.  But never allow this call to wait.
	 * If the user provided aditional options, like trailer
	 * options, pass those through here.  But we don't support
	 * scatter lists through this interface.
	 */
	self->ith_object = object;
	self->ith_msg_addr = addr;
	self->ith_rsize = size;
	self->ith_msize = 0;
	self->ith_option = option;
	self->ith_receiver_name = MACH_PORT_NULL;
	self->ith_continuation = NULL;
	option |= MACH_RCV_TIMEOUT; // never wait
	self->ith_state = MACH_RCV_IN_PROGRESS;
	self->ith_knote = kn;

	wresult = ipc_mqueue_receive_on_thread(
			mqueue,
			option,
			size, /* max_size */
			0, /* immediate timeout */
			THREAD_INTERRUPTIBLE,
			self);
	/* mqueue unlocked */

	/*
	 * If we timed out, or the process is exiting, just release the
	 * reference on the ipc_object and return zero.
	 */
	if (wresult == THREAD_RESTART || self->ith_state == MACH_RCV_TIMED_OUT) {
		assert(self->turnstile != TURNSTILE_NULL);
		io_release(object);
		return 0;
	}

	assert(wresult == THREAD_NOT_WAITING);
	assert(self->ith_state != MACH_RCV_IN_PROGRESS);

	/*
	 * If we weren't attempting to receive a message
	 * directly, we need to return the port name in
	 * the kevent structure.
	 */
	if ((option & MACH_RCV_MSG) != MACH_RCV_MSG) {
		assert(self->ith_state == MACH_RCV_TOO_LARGE);
		assert(self->ith_kmsg == IKM_NULL);
		kev->data = self->ith_receiver_name;
		io_release(object);
		return FILTER_ACTIVE;
	}

	/*
	 * Attempt to receive the message directly, returning
	 * the results in the fflags field.
	 */
	kev->fflags = mach_msg_receive_results(&size);

	/* kmsg and object reference consumed */

	/*
	 * if the user asked for the identity of ports containing a
	 * a too-large message, return it in the data field (as we
	 * do for messages we didn't try to receive).
	 */
	if (kev->fflags == MACH_RCV_TOO_LARGE) {
		kev->ext[1] = self->ith_msize;
		if (option & MACH_RCV_LARGE_IDENTITY)
			kev->data = self->ith_receiver_name;
		else
			kev->data = MACH_PORT_NULL;
	} else {
		kev->ext[1] = size;
		kev->data = MACH_PORT_NULL;
	}

	/*
	 * If we used a data buffer carved out from the filt_process data,
	 * store the address used in the knote and adjust the residual and
	 * other parameters for future use.
	 */
	if (used_filtprocess_data) {
		assert(process_data->fp_data_resid >= size);
		process_data->fp_data_resid -= size;
		if ((process_data->fp_flags & KEVENT_FLAG_STACK_DATA) == 0) {
			kev->ext[0] = process_data->fp_data_out;
			process_data->fp_data_out += size;
		} else {
			assert(option & MACH_RCV_STACK);
			kev->ext[0] = process_data->fp_data_out +
				      process_data->fp_data_resid;
		}
	}

	/*
	 * Apply message-based QoS values to output kevent as prescribed.
	 * The kev->ext[2] field gets (msg-qos << 32) | (override-qos).
	 *
	 * The mach_msg_receive_results() call saved off the message
	 * QoS values in the continuation save area on successful receive.
	 */
	if (kev->fflags == MACH_MSG_SUCCESS) {
		kev->ext[2] = ((uint64_t)self->ith_qos << 32) |
				(uint64_t)self->ith_qos_override;
	}

	return FILTER_ACTIVE;
}