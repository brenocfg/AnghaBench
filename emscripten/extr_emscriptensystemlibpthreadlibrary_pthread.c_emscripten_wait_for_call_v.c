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
struct TYPE_3__ {int /*<<< orphan*/  operationDone; } ;
typedef  TYPE_1__ em_queued_call ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  EMSCRIPTEN_RESULT_TIMED_OUT ; 
 int /*<<< orphan*/  EM_THREAD_STATUS_RUNNING ; 
 int /*<<< orphan*/  EM_THREAD_STATUS_WAITPROXY ; 
 int emscripten_atomic_load_u32 (int /*<<< orphan*/ *) ; 
 int emscripten_futex_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 double emscripten_get_now () ; 
 int /*<<< orphan*/  emscripten_set_current_thread_status (int /*<<< orphan*/ ) ; 

EMSCRIPTEN_RESULT emscripten_wait_for_call_v(em_queued_call *call, double timeoutMSecs)
{
	int r;

	int done = emscripten_atomic_load_u32(&call->operationDone);
	if (!done) {
		double now = emscripten_get_now();
		double waitEndTime = now + timeoutMSecs;
		emscripten_set_current_thread_status(EM_THREAD_STATUS_WAITPROXY);
		while(!done && now < waitEndTime) {
			r = emscripten_futex_wait(&call->operationDone, 0, waitEndTime - now);
			done = emscripten_atomic_load_u32(&call->operationDone);
			now = emscripten_get_now();
		}
		emscripten_set_current_thread_status(EM_THREAD_STATUS_RUNNING);
	}
	if (done) return EMSCRIPTEN_RESULT_SUCCESS;
	else return EMSCRIPTEN_RESULT_TIMED_OUT;
}