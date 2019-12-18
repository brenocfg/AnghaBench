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
struct p9_conn {scalar_t__ err; int /*<<< orphan*/  wq; int /*<<< orphan*/  wsched; int /*<<< orphan*/  unsent_req_list; scalar_t__ wsize; int /*<<< orphan*/  rq; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_conn*,...) ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int /*<<< orphan*/  Rpending ; 
 int /*<<< orphan*/  Rworksched ; 
 int /*<<< orphan*/  Wpending ; 
 int /*<<< orphan*/  Wworksched ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_conn_cancel (struct p9_conn*,int) ; 
 int p9_fd_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p9_poll_mux(struct p9_conn *m)
{
	int n;

	if (m->err < 0)
		return;

	n = p9_fd_poll(m->client, NULL);
	if (n < 0 || n & (POLLERR | POLLHUP | POLLNVAL)) {
		P9_DPRINTK(P9_DEBUG_TRANS, "error mux %p err %d\n", m, n);
		if (n >= 0)
			n = -ECONNRESET;
		p9_conn_cancel(m, n);
	}

	if (n & POLLIN) {
		set_bit(Rpending, &m->wsched);
		P9_DPRINTK(P9_DEBUG_TRANS, "mux %p can read\n", m);
		if (!test_and_set_bit(Rworksched, &m->wsched)) {
			P9_DPRINTK(P9_DEBUG_TRANS, "sched read work %p\n", m);
			schedule_work(&m->rq);
		}
	}

	if (n & POLLOUT) {
		set_bit(Wpending, &m->wsched);
		P9_DPRINTK(P9_DEBUG_TRANS, "mux %p can write\n", m);
		if ((m->wsize || !list_empty(&m->unsent_req_list))
		    && !test_and_set_bit(Wworksched, &m->wsched)) {
			P9_DPRINTK(P9_DEBUG_TRANS, "sched write work %p\n", m);
			schedule_work(&m->wq);
		}
	}
}