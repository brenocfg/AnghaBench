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
struct smb_sb_info {int dummy; } ;
struct smb_request {unsigned char* rq_buffer; int rq_bufsize; int /*<<< orphan*/  rq_count; int /*<<< orphan*/  rq_queue; int /*<<< orphan*/  rq_wait; struct smb_sb_info* rq_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERBOSE (char*,struct smb_request*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct smb_request*) ; 
 struct smb_request* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_cachep ; 

__attribute__((used)) static struct smb_request *smb_do_alloc_request(struct smb_sb_info *server,
						int bufsize)
{
	struct smb_request *req;
	unsigned char *buf = NULL;

	req = kmem_cache_zalloc(req_cachep, GFP_KERNEL);
	VERBOSE("allocating request: %p\n", req);
	if (!req)
		goto out;

	if (bufsize > 0) {
		buf = kmalloc(bufsize, GFP_NOFS);
		if (!buf) {
			kmem_cache_free(req_cachep, req);
			return NULL;
		}
	}

	req->rq_buffer = buf;
	req->rq_bufsize = bufsize;
	req->rq_server = server;
	init_waitqueue_head(&req->rq_wait);
	INIT_LIST_HEAD(&req->rq_queue);
	atomic_set(&req->rq_count, 1);

out:
	return req;
}