#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gru_control_block_status {int icmd; } ;
struct control_block_extended_exc_detail {int ecause; int cbrexecstatus; } ;

/* Variables and functions */
 int CBR_EXS_ABORT_OCC ; 
 int CBS_EXCEPTION ; 
 scalar_t__ CBS_IDLE ; 
 int EXCEPTION_RETRY_BITS ; 
 int EXCEPTION_RETRY_LIMIT ; 
 int /*<<< orphan*/  gru_flush_cache (struct gru_control_block_status*) ; 
 int /*<<< orphan*/  gru_get_cb_exception_detail (void*,struct control_block_extended_exc_detail*) ; 
 scalar_t__ gru_get_cb_message_queue_substatus (void*) ; 
 scalar_t__ gru_wait_idle_or_exception (struct gru_control_block_status*) ; 

__attribute__((used)) static int gru_retry_exception(void *cb)
{
	struct gru_control_block_status *gen = (void *)cb;
	struct control_block_extended_exc_detail excdet;
	int retry = EXCEPTION_RETRY_LIMIT;

	while (1)  {
		if (gru_wait_idle_or_exception(gen) == CBS_IDLE)
			return CBS_IDLE;
		if (gru_get_cb_message_queue_substatus(cb))
			return CBS_EXCEPTION;
		gru_get_cb_exception_detail(cb, &excdet);
		if ((excdet.ecause & ~EXCEPTION_RETRY_BITS) ||
				(excdet.cbrexecstatus & CBR_EXS_ABORT_OCC))
			break;
		if (retry-- == 0)
			break;
		gen->icmd = 1;
		gru_flush_cache(gen);
	}
	return CBS_EXCEPTION;
}