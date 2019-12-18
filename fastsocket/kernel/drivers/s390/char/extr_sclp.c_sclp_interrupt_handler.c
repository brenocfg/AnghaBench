#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sclp_req {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct sclp_req*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int ext_params; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  SCLP_REQ_DONE ; 
 struct sclp_req* __sclp_find_req (int) ; 
 int /*<<< orphan*/  __sclp_queue_read_req () ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ sclp_activation_state ; 
 scalar_t__ sclp_activation_state_active ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_process_queue () ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 int /*<<< orphan*/  sclp_running_state ; 
 int /*<<< orphan*/  sclp_running_state_idle ; 
 int /*<<< orphan*/  sclp_running_state_reset_pending ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sclp_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sclp_interrupt_handler(__u16 code)
{
	struct sclp_req *req;
	u32 finished_sccb;
	u32 evbuf_pending;

	spin_lock(&sclp_lock);
	finished_sccb = S390_lowcore.ext_params & 0xfffffff8;
	evbuf_pending = S390_lowcore.ext_params & 0x3;
	if (finished_sccb) {
		del_timer(&sclp_request_timer);
		sclp_running_state = sclp_running_state_reset_pending;
		req = __sclp_find_req(finished_sccb);
		if (req) {
			/* Request post-processing */
			list_del(&req->list);
			req->status = SCLP_REQ_DONE;
			if (req->callback) {
				spin_unlock(&sclp_lock);
				req->callback(req, req->callback_data);
				spin_lock(&sclp_lock);
			}
		}
		sclp_running_state = sclp_running_state_idle;
	}
	if (evbuf_pending &&
	    sclp_activation_state == sclp_activation_state_active)
		__sclp_queue_read_req();
	spin_unlock(&sclp_lock);
	sclp_process_queue();
}