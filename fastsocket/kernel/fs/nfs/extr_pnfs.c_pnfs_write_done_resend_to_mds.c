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
struct nfs_pgio_completion_ops {int dummy; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct nfs_page {int dummy; } ;
struct list_head {int /*<<< orphan*/  next; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FLUSH_STABLE ; 
 int /*<<< orphan*/  LIST_HEAD (struct list_head) ; 
 struct list_head failed ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,struct list_head*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_init_write (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,struct nfs_pgio_completion_ops const*) ; 

__attribute__((used)) static int pnfs_write_done_resend_to_mds(struct inode *inode,
				struct list_head *head,
				const struct nfs_pgio_completion_ops *compl_ops)
{
	struct nfs_pageio_descriptor pgio;
	LIST_HEAD(failed);

	/* Resend all requests through the MDS */
	nfs_pageio_init_write(&pgio, inode, FLUSH_STABLE, compl_ops);
	while (!list_empty(head)) {
		struct nfs_page *req = nfs_list_entry(head->next);

		nfs_list_remove_request(req);
		if (!nfs_pageio_add_request(&pgio, req))
			nfs_list_add_request(req, &failed);
	}
	nfs_pageio_complete(&pgio);

	if (!list_empty(&failed)) {
		/* For some reason our attempt to resend pages. Mark the
		 * overall send request as having failed, and let
		 * nfs_writeback_release_full deal with the error.
		 */
		list_move(&failed, head);
		return -EIO;
	}
	return 0;
}