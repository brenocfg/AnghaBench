#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_14__ {int numargs; int argvar; int argpages; TYPE_6__* args; } ;
struct cuse_init_in {int /*<<< orphan*/  flags; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_11__ {int /*<<< orphan*/  cuse_init_out; struct cuse_init_in cuse_init_in; } ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {int num_pages; int /*<<< orphan*/  end; TYPE_7__ out; TYPE_5__* page_descs; struct page** pages; TYPE_4__ misc; TYPE_3__ in; } ;
struct fuse_conn {int dummy; } ;
struct cuse_init_out {int dummy; } ;
struct cuse_conn {struct fuse_conn fc; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/ * value; } ;
struct TYPE_12__ {int length; } ;
struct TYPE_9__ {int size; struct cuse_init_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CUSE_INIT ; 
 int CUSE_INIT_INFO_MAX ; 
 int /*<<< orphan*/  CUSE_UNRESTRICTED_IOCTL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_KERNEL_MINOR_VERSION ; 
 int /*<<< orphan*/  FUSE_KERNEL_VERSION ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct fuse_req*) ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  cuse_process_init_reply ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send_background (struct fuse_conn*,struct fuse_req*) ; 

__attribute__((used)) static int cuse_send_init(struct cuse_conn *cc)
{
	int rc;
	struct fuse_req *req;
	struct page *page;
	struct fuse_conn *fc = &cc->fc;
	struct cuse_init_in *arg;

	BUILD_BUG_ON(CUSE_INIT_INFO_MAX > PAGE_SIZE);

	req = fuse_get_req(fc, 1);
	if (IS_ERR(req)) {
		rc = PTR_ERR(req);
		goto err;
	}

	rc = -ENOMEM;
	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		goto err_put_req;

	arg = &req->misc.cuse_init_in;
	arg->major = FUSE_KERNEL_VERSION;
	arg->minor = FUSE_KERNEL_MINOR_VERSION;
	arg->flags |= CUSE_UNRESTRICTED_IOCTL;
	req->in.h.opcode = CUSE_INIT;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(struct cuse_init_in);
	req->in.args[0].value = arg;
	req->out.numargs = 2;
	req->out.args[0].size = sizeof(struct cuse_init_out);
	req->out.args[0].value = &req->misc.cuse_init_out;
	req->out.args[1].size = CUSE_INIT_INFO_MAX;
	req->out.argvar = 1;
	req->out.argpages = 1;
	req->pages[0] = page;
	req->page_descs[0].length = req->out.args[1].size;
	req->num_pages = 1;
	req->end = cuse_process_init_reply;
	fuse_request_send_background(fc, req);

	return 0;

err_put_req:
	fuse_put_request(fc, req);
err:
	return rc;
}