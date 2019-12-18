#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_pageio_descriptor {TYPE_1__* pg_ops; } ;
struct nfs_page {scalar_t__ wb_pgbase; scalar_t__ wb_bytes; int /*<<< orphan*/  wb_lock_context; TYPE_4__* wb_context; } ;
struct TYPE_9__ {TYPE_2__* dentry; } ;
struct TYPE_8__ {int /*<<< orphan*/ * i_flock; } ;
struct TYPE_7__ {TYPE_3__* d_inode; } ;
struct TYPE_6__ {int (* pg_test ) (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ;} ;

/* Variables and functions */
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  nfs_match_lock_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_match_open_context (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 
 int stub1 (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 

__attribute__((used)) static bool nfs_can_coalesce_requests(struct nfs_page *prev,
				      struct nfs_page *req,
				      struct nfs_pageio_descriptor *pgio)
{
	if (!nfs_match_open_context(req->wb_context, prev->wb_context))
		return false;
	if (req->wb_context->dentry->d_inode->i_flock != NULL &&
	    !nfs_match_lock_context(req->wb_lock_context, prev->wb_lock_context))
		return false;
	if (req->wb_pgbase != 0)
		return false;
	if (prev->wb_pgbase + prev->wb_bytes != PAGE_CACHE_SIZE)
		return false;
	if (req_offset(req) != req_offset(prev) + prev->wb_bytes)
		return false;
	return pgio->pg_ops->pg_test(pgio, prev, req);
}