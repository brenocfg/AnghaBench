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
struct page {TYPE_1__* mapping; } ;
struct nfs_page {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 struct nfs_page* nfs_create_request (struct nfs_open_context*,struct inode*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_inode_add_request (struct inode*,struct nfs_page*) ; 
 struct nfs_page* nfs_try_to_update_request (struct inode*,struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static struct nfs_page * nfs_setup_write_request(struct nfs_open_context* ctx,
		struct page *page, unsigned int offset, unsigned int bytes)
{
	struct inode *inode = page->mapping->host;
	struct nfs_page	*req;

	req = nfs_try_to_update_request(inode, page, offset, bytes);
	if (req != NULL)
		goto out;
	req = nfs_create_request(ctx, inode, page, offset, bytes);
	if (IS_ERR(req))
		goto out;
	nfs_inode_add_request(inode, req);
out:
	return req;
}