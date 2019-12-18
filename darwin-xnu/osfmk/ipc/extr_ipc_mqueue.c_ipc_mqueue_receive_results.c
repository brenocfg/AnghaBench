#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int wait_result_t ;
typedef  TYPE_1__* thread_t ;
typedef  int mach_msg_option_t ;
struct TYPE_3__ {int ith_option; int /*<<< orphan*/  ith_state; } ;

/* Variables and functions */
#define  MACH_MSG_SUCCESS 135 
#define  MACH_PEEK_READY 134 
 int /*<<< orphan*/  MACH_RCV_INTERRUPTED ; 
 int MACH_RCV_LARGE ; 
 int /*<<< orphan*/  MACH_RCV_PORT_CHANGED ; 
#define  MACH_RCV_SCATTER_SMALL 133 
 int /*<<< orphan*/  MACH_RCV_TIMED_OUT ; 
#define  MACH_RCV_TOO_LARGE 132 
#define  THREAD_AWAKENED 131 
#define  THREAD_INTERRUPTED 130 
#define  THREAD_RESTART 129 
#define  THREAD_TIMED_OUT 128 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_mqueue_receive_results(wait_result_t saved_wait_result)
{
	thread_t     		self = current_thread();
	mach_msg_option_t	option = self->ith_option;

	/*
	 * why did we wake up?
	 */
	switch (saved_wait_result) {
	case THREAD_TIMED_OUT:
		self->ith_state = MACH_RCV_TIMED_OUT;
		return;

	case THREAD_INTERRUPTED:
		self->ith_state = MACH_RCV_INTERRUPTED;
		return;

	case THREAD_RESTART:
		/* something bad happened to the port/set */
		self->ith_state = MACH_RCV_PORT_CHANGED;
		return;

	case THREAD_AWAKENED:
		/*
		 * We do not need to go select a message, somebody
		 * handed us one (or a too-large indication).
		 */
		switch (self->ith_state) {
		case MACH_RCV_SCATTER_SMALL:
		case MACH_RCV_TOO_LARGE:
			/*
			 * Somebody tried to give us a too large
			 * message. If we indicated that we cared,
			 * then they only gave us the indication,
			 * otherwise they gave us the indication
			 * AND the message anyway.
			 */
			if (option & MACH_RCV_LARGE) {
				return;
			}

		case MACH_MSG_SUCCESS:
		case MACH_PEEK_READY:
			return;

		default:
			panic("ipc_mqueue_receive_results: strange ith_state");
		}

	default:
		panic("ipc_mqueue_receive_results: strange wait_result");
	}
}