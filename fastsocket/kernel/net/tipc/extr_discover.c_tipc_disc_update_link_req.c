#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct link_req {scalar_t__ timer_intv; int /*<<< orphan*/  timer; TYPE_2__* bearer; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ nodes; } ;

/* Variables and functions */
 scalar_t__ TIPC_LINK_REQ_FAST ; 
 scalar_t__ TIPC_LINK_REQ_SLOW ; 
 int /*<<< orphan*/  k_start_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void tipc_disc_update_link_req(struct link_req *req)
{
	if (!req)
		return;

	if (req->timer_intv == TIPC_LINK_REQ_SLOW) {
		if (!req->bearer->nodes.count) {
			req->timer_intv = TIPC_LINK_REQ_FAST;
			k_start_timer(&req->timer, req->timer_intv);
		}
	} else if (req->timer_intv == TIPC_LINK_REQ_FAST) {
		if (req->bearer->nodes.count) {
			req->timer_intv = TIPC_LINK_REQ_SLOW;
			k_start_timer(&req->timer, req->timer_intv);
		}
	} else {
		/* leave timer "as is" if haven't yet reached a "normal" rate */
	}
}