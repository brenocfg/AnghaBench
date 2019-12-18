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
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EBADF ; 
 int ESTALE ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  NFSIOS_READPAGES ; 
 int /*<<< orphan*/  NFSIOS_VFSREADPAGE ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  dprintk (char*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_open_context* get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 struct nfs_open_context* nfs_find_open_context (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_readpage_async (struct nfs_open_context*,struct inode*,struct page*) ; 
 int nfs_readpage_from_fscache (struct nfs_open_context*,struct inode*,struct page*) ; 
 int nfs_wb_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nfs_readpage(struct file *file, struct page *page)
{
	struct nfs_open_context *ctx;
	struct inode *inode = page->mapping->host;
	int		error;

	dprintk("NFS: nfs_readpage (%p %ld@%lu)\n",
		page, PAGE_CACHE_SIZE, page->index);
	nfs_inc_stats(inode, NFSIOS_VFSREADPAGE);
	nfs_add_stats(inode, NFSIOS_READPAGES, 1);

	/*
	 * Try to flush any pending writes to the file..
	 *
	 * NOTE! Because we own the page lock, there cannot
	 * be any new pending writes generated at this point
	 * for this page (other pages can be written to).
	 */
	error = nfs_wb_page(inode, page);
	if (error)
		goto out_unlock;
	if (PageUptodate(page))
		goto out_unlock;

	error = -ESTALE;
	if (NFS_STALE(inode))
		goto out_unlock;

	if (file == NULL) {
		error = -EBADF;
		ctx = nfs_find_open_context(inode, NULL, FMODE_READ);
		if (ctx == NULL)
			goto out_unlock;
	} else
		ctx = get_nfs_open_context(nfs_file_open_context(file));

	if (!IS_SYNC(inode)) {
		error = nfs_readpage_from_fscache(ctx, inode, page);
		if (error == 0)
			goto out;
	}

	error = nfs_readpage_async(ctx, inode, page);

out:
	put_nfs_open_context(ctx);
	return error;
out_unlock:
	unlock_page(page);
	return error;
}