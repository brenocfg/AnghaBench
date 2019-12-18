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
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct nfs_pageio_descriptor {scalar_t__ pg_error; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_pageio_init ) (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_2__* NFS_PROTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_async_write_completion_ops ; 
 int nfs_do_writepage (struct page*,struct writeback_control*,struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_priority (struct writeback_control*) ; 

__attribute__((used)) static int nfs_writepage_locked(struct page *page, struct writeback_control *wbc)
{
	struct nfs_pageio_descriptor pgio;
	int err;

	NFS_PROTO(page->mapping->host)->write_pageio_init(&pgio,
							  page->mapping->host,
							  wb_priority(wbc),
							  &nfs_async_write_completion_ops);
	err = nfs_do_writepage(page, wbc, &pgio);
	nfs_pageio_complete(&pgio);
	if (err < 0)
		return err;
	if (pgio.pg_error < 0)
		return pgio.pg_error;
	return 0;
}