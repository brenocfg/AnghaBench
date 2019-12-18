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
struct link_req {int /*<<< orphan*/  buf; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_cancel_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_term_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct link_req*) ; 

void tipc_disc_stop_link_req(struct link_req *req)
{
	if (!req)
		return;

	k_cancel_timer(&req->timer);
	k_term_timer(&req->timer);
	buf_discard(req->buf);
	kfree(req);
}