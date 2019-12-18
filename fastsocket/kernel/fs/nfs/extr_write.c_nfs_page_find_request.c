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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct nfs_page* nfs_page_find_request_locked (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_page *nfs_page_find_request(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct nfs_page *req = NULL;

	spin_lock(&inode->i_lock);
	req = nfs_page_find_request_locked(page);
	spin_unlock(&inode->i_lock);
	return req;
}