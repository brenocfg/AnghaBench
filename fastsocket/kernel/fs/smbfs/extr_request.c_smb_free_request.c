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
struct smb_request {int rq_flags; scalar_t__ rq_trans2buffer; scalar_t__ rq_buffer; TYPE_1__* rq_server; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_requests; } ;

/* Variables and functions */
 int SMB_REQ_STATIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct smb_request*) ; 
 int /*<<< orphan*/  req_cachep ; 

__attribute__((used)) static void smb_free_request(struct smb_request *req)
{
	atomic_dec(&req->rq_server->nr_requests);
	if (req->rq_buffer && !(req->rq_flags & SMB_REQ_STATIC))
		kfree(req->rq_buffer);
	kfree(req->rq_trans2buffer);
	kmem_cache_free(req_cachep, req);
}