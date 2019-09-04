#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  turnstile_inheritor_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  scalar_t__ mach_msg_timeout_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  int mach_msg_option_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  TYPE_3__* ipc_mqueue_t ;
typedef  TYPE_4__* ipc_kmsg_t ;
struct TYPE_21__ {TYPE_1__* ikm_header; } ;
struct TYPE_20__ {scalar_t__ imq_msgcount; int /*<<< orphan*/  imq_fullwaiters; } ;
struct TYPE_19__ {scalar_t__ ip_receiver_name; int /*<<< orphan*/ * ip_destination; } ;
struct TYPE_18__ {int /*<<< orphan*/  msgh_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_MQUEUE_FULL ; 
 scalar_t__ MACH_MSGH_BITS_REMOTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 scalar_t__ MACH_MSG_TYPE_PORT_SEND_ONCE ; 
 scalar_t__ MACH_PORT_NULL ; 
 int MACH_SEND_ALWAYS ; 
 int /*<<< orphan*/  MACH_SEND_INTERRUPTED ; 
 int /*<<< orphan*/  MACH_SEND_INVALID_DEST ; 
 int /*<<< orphan*/  MACH_SEND_NO_BUFFER ; 
 int /*<<< orphan*/  MACH_SEND_TIMED_OUT ; 
 int MACH_SEND_TIMEOUT ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
#define  THREAD_AWAKENED 131 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
#define  THREAD_INTERRUPTED 130 
#define  THREAD_RESTART 129 
#define  THREAD_TIMED_OUT 128 
 int THREAD_WAITING ; 
 int /*<<< orphan*/  TIMEOUT_NO_LEEWAY ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_USER_NORMAL ; 
 int /*<<< orphan*/  TRUE ; 
 int TURNSTILE_DELAYED_UPDATE ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_NULL ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_SYNC_IPC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_ipc_mqueue_send_block ; 
 int /*<<< orphan*/  clock_interval_to_deadline (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  imq_full (TYPE_3__*) ; 
 scalar_t__ imq_full_kernel (TYPE_3__*) ; 
 int /*<<< orphan*/  imq_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_3__*) ; 
 scalar_t__ ip_active (TYPE_2__*) ; 
 TYPE_2__* ip_from_mq (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_mqueue_post (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ipc_port_get_inheritor (TYPE_2__*) ; 
 int /*<<< orphan*/  kThreadWaitPortSend ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  port_send_turnstile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_send_turnstile_address (TYPE_2__*) ; 
 int thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_pending_block_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_prepare (uintptr_t,int /*<<< orphan*/ ,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 
 int waitq_assert_wait64_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

mach_msg_return_t
ipc_mqueue_send(
	ipc_mqueue_t		mqueue,
	ipc_kmsg_t		kmsg,
	mach_msg_option_t	option,
	mach_msg_timeout_t  send_timeout)
{
	int wresult;

	/*
	 *  Don't block if:
	 *	1) We're under the queue limit.
	 *	2) Caller used the MACH_SEND_ALWAYS internal option.
	 *	3) Message is sent to a send-once right.
	 */
	if (!imq_full(mqueue) ||
	    (!imq_full_kernel(mqueue) &&
	     ((option & MACH_SEND_ALWAYS) ||
	      (MACH_MSGH_BITS_REMOTE(kmsg->ikm_header->msgh_bits) ==
	       MACH_MSG_TYPE_PORT_SEND_ONCE)))) {
		mqueue->imq_msgcount++;
		assert(mqueue->imq_msgcount > 0);
		imq_unlock(mqueue);
	} else {
		thread_t cur_thread = current_thread();
		ipc_port_t port = ip_from_mq(mqueue);
		struct turnstile *send_turnstile = TURNSTILE_NULL;
		turnstile_inheritor_t inheritor = TURNSTILE_INHERITOR_NULL;
		uint64_t deadline;

		/*
		 * We have to wait for space to be granted to us.
		 */
		if ((option & MACH_SEND_TIMEOUT) && (send_timeout == 0)) {
			imq_unlock(mqueue);
			return MACH_SEND_TIMED_OUT;
		}
		if (imq_full_kernel(mqueue)) {
			imq_unlock(mqueue);
			return MACH_SEND_NO_BUFFER;
		}
		mqueue->imq_fullwaiters = TRUE;

		if (option & MACH_SEND_TIMEOUT)
			clock_interval_to_deadline(send_timeout, 1000*NSEC_PER_USEC, &deadline);
		else
			deadline = 0;

		thread_set_pending_block_hint(cur_thread, kThreadWaitPortSend);

		send_turnstile = turnstile_prepare((uintptr_t)port,
			port_send_turnstile_address(port),
			TURNSTILE_NULL, TURNSTILE_SYNC_IPC);

		/* Check if the port in is in transit, get the destination port's turnstile */
		if (ip_active(port) &&
		    port->ip_receiver_name == MACH_PORT_NULL &&
		    port->ip_destination != NULL) {
			inheritor = port_send_turnstile(port->ip_destination);
		} else {
			inheritor = ipc_port_get_inheritor(port);
		}

		turnstile_update_inheritor(send_turnstile, inheritor,
				TURNSTILE_DELAYED_UPDATE | TURNSTILE_INHERITOR_TURNSTILE);

		wresult = waitq_assert_wait64_leeway(
					&send_turnstile->ts_waitq,
					IPC_MQUEUE_FULL,
					THREAD_ABORTSAFE,
					TIMEOUT_URGENCY_USER_NORMAL,
					deadline,
					TIMEOUT_NO_LEEWAY);

		imq_unlock(mqueue);
		turnstile_update_inheritor_complete(send_turnstile,
				TURNSTILE_INTERLOCK_NOT_HELD);

		if (wresult == THREAD_WAITING) {
			wresult = thread_block(THREAD_CONTINUE_NULL);
			counter(c_ipc_mqueue_send_block++);
		}

		/* Call turnstile complete with interlock held */
		imq_lock(mqueue);
		turnstile_complete((uintptr_t)port, port_send_turnstile_address(port), NULL);
		imq_unlock(mqueue);

		/* Call cleanup after dropping the interlock */
		turnstile_cleanup();

		switch (wresult) {

		case THREAD_AWAKENED:
			/*
			 * we can proceed - inherited msgcount from waker
			 * or the message queue has been destroyed and the msgcount
			 * has been reset to zero (will detect in ipc_mqueue_post()).
			 */
			break;

		case THREAD_TIMED_OUT:
			assert(option & MACH_SEND_TIMEOUT);
			return MACH_SEND_TIMED_OUT;

		case THREAD_INTERRUPTED:
			return MACH_SEND_INTERRUPTED;

		case THREAD_RESTART:
			/* mqueue is being destroyed */
			return MACH_SEND_INVALID_DEST;
		default:
			panic("ipc_mqueue_send");
		}
	}

	ipc_mqueue_post(mqueue, kmsg, option);
	return MACH_MSG_SUCCESS;
}