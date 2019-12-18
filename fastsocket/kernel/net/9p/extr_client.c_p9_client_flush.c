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
struct p9_req_t {scalar_t__ status; int /*<<< orphan*/  req_list; int /*<<< orphan*/  tc; } ;
struct p9_client {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P9_TFLUSH ; 
 int PTR_ERR (struct p9_req_t*) ; 
 scalar_t__ REQ_STATUS_FLSH ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_free_req (struct p9_client*,struct p9_req_t*) ; 
 int p9_parse_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_client_flush(struct p9_client *c, struct p9_req_t *oldreq)
{
	struct p9_req_t *req;
	int16_t oldtag;
	int err;

	err = p9_parse_header(oldreq->tc, NULL, NULL, &oldtag, 1);
	if (err)
		return err;

	P9_DPRINTK(P9_DEBUG_9P, ">>> TFLUSH tag %d\n", oldtag);

	req = p9_client_rpc(c, P9_TFLUSH, "w", oldtag);
	if (IS_ERR(req))
		return PTR_ERR(req);


	/* if we haven't received a response for oldreq,
	   remove it from the list. */
	spin_lock(&c->lock);
	if (oldreq->status == REQ_STATUS_FLSH)
		list_del(&oldreq->req_list);
	spin_unlock(&c->lock);

	p9_free_req(c, req);
	return 0;
}