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
struct ncp_request_reply {int /*<<< orphan*/  status; int /*<<< orphan*/  refs; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RQ_IDLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ncp_request_reply* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ncp_request_reply* ncp_alloc_req(void)
{
	struct ncp_request_reply *req;

	req = kmalloc(sizeof(struct ncp_request_reply), GFP_KERNEL);
	if (!req)
		return NULL;

	init_waitqueue_head(&req->wq);
	atomic_set(&req->refs, (1));
	req->status = RQ_IDLE;

	return req;
}