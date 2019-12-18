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
struct page {int dummy; } ;
struct TYPE_2__ {struct page** pagevec; } ;
struct nfs_read_data {int /*<<< orphan*/  list; TYPE_1__ pages; } ;
struct nfs_pgio_header {int /*<<< orphan*/  rpc_list; int /*<<< orphan*/  pages; } ;
struct list_head {int /*<<< orphan*/  next; } ;
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_rpc_callops; int /*<<< orphan*/  pg_count; int /*<<< orphan*/  pg_base; struct list_head pg_list; } ;
struct nfs_page {int /*<<< orphan*/  wb_page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,int /*<<< orphan*/ *) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_array_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pagein_error (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_read_common_ops ; 
 int /*<<< orphan*/  nfs_read_rpcsetup (struct nfs_read_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_read_data* nfs_readdata_alloc (struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_pagein_one(struct nfs_pageio_descriptor *desc,
			  struct nfs_pgio_header *hdr)
{
	struct nfs_page		*req;
	struct page		**pages;
	struct nfs_read_data    *data;
	struct list_head *head = &desc->pg_list;

	data = nfs_readdata_alloc(hdr, nfs_page_array_len(desc->pg_base,
							  desc->pg_count));
	if (!data) {
		nfs_pagein_error(desc, hdr);
		return -ENOMEM;
	}

	pages = data->pages.pagevec;
	while (!list_empty(head)) {
		req = nfs_list_entry(head->next);
		nfs_list_remove_request(req);
		nfs_list_add_request(req, &hdr->pages);
		*pages++ = req->wb_page;
	}

	nfs_read_rpcsetup(data, desc->pg_count, 0);
	list_add(&data->list, &hdr->rpc_list);
	desc->pg_rpc_callops = &nfs_read_common_ops;
	return 0;
}