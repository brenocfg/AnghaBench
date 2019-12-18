#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_3__ {struct page** pagevec; } ;
struct nfs_write_data {int /*<<< orphan*/  list; TYPE_1__ pages; } ;
struct nfs_pgio_header {int /*<<< orphan*/  pages; int /*<<< orphan*/  rpc_list; struct nfs_page* req; } ;
struct nfs_pageio_descriptor {int pg_ioflags; size_t pg_count; int /*<<< orphan*/ * pg_rpc_callops; scalar_t__ pg_moreio; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {struct page* wb_page; } ;
struct nfs_commit_info {int dummy; } ;
struct TYPE_4__ {size_t wsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FLUSH_COND_STABLE ; 
 TYPE_2__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  nfs_flush_error (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 scalar_t__ nfs_reqs_to_commit (struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_write_common_ops ; 
 int /*<<< orphan*/  nfs_write_rpcsetup (struct nfs_write_data*,size_t,unsigned int,int,struct nfs_commit_info*) ; 
 struct nfs_write_data* nfs_writedata_alloc (struct nfs_pgio_header*,int) ; 

__attribute__((used)) static int nfs_flush_multi(struct nfs_pageio_descriptor *desc,
			   struct nfs_pgio_header *hdr)
{
	struct nfs_page *req = hdr->req;
	struct page *page = req->wb_page;
	struct nfs_write_data *data;
	size_t wsize = NFS_SERVER(desc->pg_inode)->wsize, nbytes;
	unsigned int offset;
	int requests = 0;
	struct nfs_commit_info cinfo;

	nfs_init_cinfo(&cinfo, desc->pg_inode, desc->pg_dreq);

	if ((desc->pg_ioflags & FLUSH_COND_STABLE) &&
	    (desc->pg_moreio || nfs_reqs_to_commit(&cinfo) ||
	     desc->pg_count > wsize))
		desc->pg_ioflags &= ~FLUSH_COND_STABLE;


	offset = 0;
	nbytes = desc->pg_count;
	do {
		size_t len = min(nbytes, wsize);

		data = nfs_writedata_alloc(hdr, 1);
		if (!data) {
			nfs_flush_error(desc, hdr);
			return -ENOMEM;
		}
		data->pages.pagevec[0] = page;
		nfs_write_rpcsetup(data, len, offset, desc->pg_ioflags, &cinfo);
		list_add(&data->list, &hdr->rpc_list);
		requests++;
		nbytes -= len;
		offset += len;
	} while (nbytes != 0);
	nfs_list_remove_request(req);
	nfs_list_add_request(req, &hdr->pages);
	desc->pg_rpc_callops = &nfs_write_common_ops;
	return 0;
}