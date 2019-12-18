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
struct p9_req_t {scalar_t__ status; int /*<<< orphan*/  req_list; } ;
struct p9_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_client*,struct p9_req_t*) ; 
 scalar_t__ REQ_STATUS_FLSH ; 
 scalar_t__ REQ_STATUS_FLSHD ; 
 scalar_t__ REQ_STATUS_SENT ; 
 scalar_t__ REQ_STATUS_UNSENT ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_fd_cancel(struct p9_client *client, struct p9_req_t *req)
{
	int ret = 1;

	P9_DPRINTK(P9_DEBUG_TRANS, "client %p req %p\n", client, req);

	spin_lock(&client->lock);

	if (req->status == REQ_STATUS_UNSENT) {
		list_del(&req->req_list);
		req->status = REQ_STATUS_FLSHD;
		ret = 0;
	} else if (req->status == REQ_STATUS_SENT)
		req->status = REQ_STATUS_FLSH;

	spin_unlock(&client->lock);

	return ret;
}