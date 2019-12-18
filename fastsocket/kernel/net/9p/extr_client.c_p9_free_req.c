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
struct p9_req_t {int /*<<< orphan*/  status; TYPE_1__* tc; } ;
struct p9_client {int /*<<< orphan*/  tagpool; } ;
struct TYPE_2__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_client*,struct p9_req_t*,int) ; 
 int P9_NOTAG ; 
 int /*<<< orphan*/  REQ_STATUS_IDLE ; 
 scalar_t__ p9_idpool_check (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_idpool_put (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p9_free_req(struct p9_client *c, struct p9_req_t *r)
{
	int tag = r->tc->tag;
	P9_DPRINTK(P9_DEBUG_MUX, "clnt %p req %p tag: %d\n", c, r, tag);

	r->status = REQ_STATUS_IDLE;
	if (tag != P9_NOTAG && p9_idpool_check(tag, c->tagpool))
		p9_idpool_put(tag, c->tagpool);
}